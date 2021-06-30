- [Deploy An EC2 Instance Lab](#deploy-an-ec2-instance-lab)
- [EC2 Launch Issues](#ec2-launch-issues)
- [EBS Volumes And IOPS](#ebs-volumes-and-iops)
- [What Is A Bastion Host?](#what-is-a-bastion-host)
- [Elastic Load Balancers](#elastic-load-balancers)
  - [Tips](#tips)
- [ELB Error Messages](#elb-error-messages)
  - [Tips](#tips-1)
- [ELB CloudWatch Metrics](#elb-cloudwatch-metrics)
  - [Tips](#tips-2)
- [Deploying An Application Load Balancer Lab](#deploying-an-application-load-balancer-lab)
- [AWS Systems Manager](#aws-systems-manager)
  - [Tips](#tips-3)
- [Placement Groups](#placement-groups)
  - [Cluster](#cluster)
  - [Partition](#partition)
  - [Spread](#spread)
  - [Tips](#tips-4)
- [Deployment & Provisioning Summary](#deployment--provisioning-summary)
- [Deployment & Provisioning Quiz](#deployment--provisioning-quiz)
  - [Key](#key)

## Deploy An EC2 Instance Lab

* From console go to EC2 and use `launch instance`
* Select AMI (OS template + optional product)
* Select instance type based on hardware requirements
* Set spot settings if desired to define your max prices and behavior on interruption (stop / terminate / hibernate). Launch groups, request valid from, persistent request, etc.
* Placement groups for related groups within the same AZ but you are limited to a single AZ, attached IAM role to the instance, etc.
* EC2 high resolution (**detailed**) custom metrics can go down to the second, but at an extra cost. This setting also determines how custom metrics are aggregated.
* T2 Unlimited allows burst beyond the normal capability of the instance at extra cost.
* Userdata is a viable way to launch instances with some set of commands run by default, but IMO it is better to have userdata install configuration management tools like ansible then run that via a git repo pull
```bash
#!/bin/bash
yum update -y && yum install httpd -y 
service httpd start && chkconfig httpd on
```
* Add storage volumes by type, size, device name, IOPS value, encryption, and delete on termination
* Tags as needed
* Security groups of course for `firewall` rules
* SSh key pairs if you need it

## EC2 Launch Issues

* Common reasons for failures:
  * Account limit for the type of instance in the region
  * Capacity exceeded at the AWS AZ level
* Options:
  * Wait a bit and see if the resources are freed up
  * Increase your limit via service ticket
  * Select different instance type
  * Buy reserved instances
  * Switch different AZ

## EBS Volumes And IOPS

* EBS volumes are created and attached to instances as if they were internal disk resources (create FS, install binaries, etc)
* Standard types are SSD currently
  * Gp2 - general purpose boot volumes
  * Io1 - provisioned IOPS
* IOPS is dependent on the size of the volume
  * Gp2 min of 100 IOPS/Gb up to 16k IOPS
  * Io1 is 50 IOPS/GB up to 64k IOPS
* At the limit of the volume IO requests start queuing and may cause the application become slow
* Two options to resolve:
  * Increase the size of the gp2 but if you are around 5.2 Tb you are maxed out and can't earn more IOPS
  * At that point change the volume class to io1, which can be done on the fly

## What Is A Bastion Host?

* On public subnet
* Allows connect to private EC2 via ssh or RDP via private networks
* Allows safely administering private instances without exposing them to the internet inbound
* Make sure you only connect from known ranges via security groups and limit ports to the connections tools
* Other instances like webservers are also in the public subnet but only allow web traffic

## Elastic Load Balancers

* Application load balancer (level 7 OSI)
  * Can inspect packets and route based on the contents to make informed balancing based on the contents of the packets. Eg, requests to example.com/sales routes to one set of servers and example.com/marketing routes to another
* Network load balancing (layer 4), the TCP layer
  * Fast performance and most expensive
* Classic (legacy version)
  * Works at both layers but is very basic. It does still exist but could age out at some point
* ALB are best for HTTP / HTTPs and you can create advanced request routing to send requests to the specific set of servers.
* NLB are best for TCP traffic where extreme performance is needed, working at millions of requests / second, but also at greater costs
* Classic for HTTP layers like X-forwarded and sticky sessions, or applications purely based on TCP protocol.
* Pre-warming your LB
  * You can cache up your load balancers based on specific needs (big sales day or new customer coming on line) and that may overload your ELB, you can request AWS pre-warm it via a service ticket so it can be ready for capacity based on expected traffic. They will want to know the time range for the increase, the expected request rate, and the total size of a typical request. The ELB will scale on it's own, but if you expect a burst of traffic all of a sudden and you don't want to wait
* ALB auto scale over time, but **does change the IP customers connect to** as new ALB's are brought online. 
* Network Load balancers resolve this using a **static IP** for each subnet to keep firewalls simple. 
* ALB can be behind NLB to get the benefits of both
* You don't need either or, you can put the ALB behind the NLB so you get the benefits of both.

### Tips

* 3 types of load balancer
  * Application
  * Network
  * Classic
  * Pre-warm if you expect a sudden and significate crease of traffic * Static Ips can be provided by the network load balancer, 1 per subnet

## ELB Error Messages

* Main errors are all 4xx / 5xx 
* Default is a 200 from classic or application
* 4xx are normally something at the client side
  * 400 - bad / malformed request
  * 401 - unauthorized user access
  * 403 - forbidden request blocked by WAF access control
  * 460 - client closed connection before the load balancer could respond
  * 463 - balancer got an X-Forwarded_for request header with > 30 IP addresses
* 5xx are normally on the server side
  * 500 - internal server error
  * 502 - bad gateway; app server closed connection
  * 503 - Service unavailable
  * 504 - Gateway timeout; app not responding
  * 561 - Unauthorized; error code from ID provider trying to authenticate a user

### Tips

* 4XX is client side error, fix the request and retry
* 5XX is server side, fix the problem with the deploy
  
## ELB CloudWatch Metrics

* Metrics are published to Cloudwatch for the balancer and for the back-end instances
* Helps to verify that the system is working as expected
* You can of course create alarms to perform actions when metrics are out of range, eg SMS or email on specific events.
* Metrics are gathered / minute
  * Health
    * **BackendConnectionErrors** - errors on backend instances
    * **HealthyHostCount** - # of healthy instances
    * **UnHealthyHostCount** - # of unhealthy instances
    * **HTTPCode_Backend_2XX,3XX,4XX,5XX** - Count of status codes
  * Performance
    * **Latency** - number of seconds taken for a registered instance to respond
    * **RequestCount** - 1 or 5 minutes interval
    * **SurgeQueueLength** - *Classic only*, number of pending requests max of 1024, additional requests will be rejected.
    * **SpilloverCount** - *Classic only*, number of rejected requests from SurgeQueueLength

### Tips

* Metrics by default to cloudwatch with alarms as normal
* Tracks health ( HealthyHostCount, Backend_2xx) and performance (Latency or RequestCount)

## Deploying An Application Load Balancer Lab

* Create an instance with apache installed and running on a public IP and a security group that allows HTTP
* Add bootstrap; 
```bash
#!/bin/bash
yum update -y && yum install httpd -y
echo "<html><body><center><h1>Hello Cloud Gurus. Here is my web page!</h1></center></body></html>" > /var/www/html/index.html
systemctl start httpd && systemctl enable httpd
```
* Enable http to the security group
* Create the ALB, also from the EC2 dashboard
* Select the AZs it will live and a security group
* Select a target group of instances that it would be routed to by instance ID or IP
* Create a health check of the load balancer 
* Create the ALB
* Test via the DNS of the load balancer, or Route 53 alias if you created that.

## AWS Systems Manager

* SSM is a management tool for getting visibility and control over your AWS infrastructure
* Integrated with cloudwatch allowing you to view your dashboards, operation data and detect problems
* Includes run command to automate operational tasks across resources for patching or package installs!
* Stop/start/terminate
* Run ansible playbook
* Run a shell script
* Need to create an IAM role and have that attached to the instance
  * In roles create role and create an EC2 service and attach the `EC2RoleforSSM`
* In SMM start by using `find resources` by tag or instance ID. You can save the results as a resource group from here.
* You can use insights (config / CloudTrail / Personal health / Trusted Advisor) as it relates to the resources you defined above
* Automation is where you can run some 'document' of actions that get run on the defined resources.
* `run command` is a key feature allowing running scripts, commands, updates, ansible, etc.
* `patch manager` allows patching the OS as you would expect
* `maintenance windows` is a cron service for running documents
* `activations` allows using systems manager with on-prem servers via an installed agent.
* `documents` location of the custom actions
* You can also use systems manager for secrets storage

### Tips

* Can control on prem or cloud recourses via agents
* Integrated with cloudwatch dashboards
* Groups inventory by logical groups
* Run commands on groups without needing to log into each one

## Placement Groups

By default instances are placed across different hardware to minimize the impact of hardware failure.

Intended to allow resilient, HA systems but lacks when applications want very low latency, high network throughput.

Placement groups control how instances are deployed in AWS.

* Cluster placement - all are in the same AZ
* Partition - Instances are created in logical segments called partitions located in separate racks with independent power and network
* Spread - Each instance is in a separate rack, a partition of 1.

### Cluster 

* Not HA since they are all in the same AZ
* All nodes in the placement group can talk to all other nodes in the group at the full internal network speed of 10 Gbps.
* Used when the application must have fast network connections

### Partition

* Can be multi-AZ
* Partitions use independent power and network
* Partitions can't share racks, reducing the impact of failure.
* Used for large distributed / replicated work

### Spread

* Each instances is independent
* Recommended when the app that has a small number of key instances that should be separated.
* Reduced risk of simultaneous failures at the rack level
* Maximum availability

### Tips

* Cluster: same AZ for low latency but same AZ.
* Partition: Multi-AZ with partitions separated to different racks
* Spread: Multi-AZ with each instance in different racks, not low latency.

## Deployment & Provisioning Summary

* Remember the common 2 reasons for instances failing to launch.
  * Account limits by instance type
  * Over all capacity limits for that instance type in the AZ
* EBS and IOPS
  * Input / Output per second 
  * Depends on size of volume
    * More IOPS by increasing the volume size up to a point (10 tb / 10,000 IOPS) after that change to provisioned IOPS
* Bastions are limited connections from the public internet without outgoing requests to manage private subnet instances without exposing them to the internet.
* 3 types of load balancers
	* Application - http / https
  * Network - tcp 
  * Classic - both but basic
* Pre-warm your balancer if you expect a big increase
* Static IP, 1 per subnet via network load balancer
* ALB can be behind a NLB
* 4xx is client side request issue
* 5xx are server side errors
* Metrics are sent to cloudwatch with alarms as normal
* Can monitor health, healthyhostcount, httpcodes
* Performance, latency, requestcount, surgequeue and spillover can indicate performance issues, last 2 are classic only
* System manager gives visibility and control over infrastructure
* Integrates with other tools like cloudwatch, trusted advisor, config, cloudtrail
* Groups inventory by logical groups
* Allows run command on a group of instances without needing to log in via agents or IAM policy attachment.

## Deployment & Provisioning Quiz 

1. Which of the following statements does NOT describe a Bastion host?
  - [ ] It does not enable internet access
  - [ ] It allows you to safely administer EC2 instances without exposing them to the internet
  - [ ] It is used for incoming SSH and RDP only
  - [ ] It allows EC2 instances to download security patches from whitelisted endpoints
2. Which of the following ELB error codes indicates a server-side issue?
  - [ ] 200
  - [ ] 300
  - [ ] 400
  - [ ] 500
3. Which of the following is most suitable for load balancing based on the content of HTTP/HTTPS request headers?
  - [ ] Application load balancer
  - [ ] Network load balancer
  - [ ] Ec2 load balancer
  - [ ] Classic load balancer
4. You would like to receive an alert if more than 3 of your application servers fail to respond at a basic health check by the Elastic Load Balancer. Which metric could you use to configure this?
  - [ ] FailedHostCount
  - [ ] UnHealthyInstanceCount
  - [ ] SpilloverCount
  - [ ] UnHealthHostCount
5. You are running your production database in MySQL on an independent EBS volume and you are fast approaching an average IOPS of 9,000. You have decided to migrate your database to an EBS volume with provisioned IOPS. Your key users only use the database between 9 am - 6 pm, so you can afford to have some down time out of hours, but not during the working day. Which is the best option below to achieve this migration.
  - [ ] Update the EBS volume where the MySQL database is running to change it's volume type from gp2 to io1. The changes will take place behind the scenes, and requires no further intervention from an administrator
  - [ ] Take a snapshot of both the root device volume and the database volume at midday. Once the snapshot is complete, terminate the EC2 instance and the database EBS volume. Restore the root device volume and EC2 instance using Provisioned IOPS SSD drives for both volumes.
  - [ ] Choose a suitable time window for your downtime. Stop the MySQL service. Move the database to S3. Restart the MySQL service, but set the configuration so that it addresses your new bucket S3://mydatabasebucket.
  - [ ] Choose a suitable time window for your downtime. Stop the MySQL service. Take a snapshot of the EBS volume where the MySQL database is running. Detach and then delete the old database volume. Restore the snapshot to a new volume running on provisioned IOPS.
6. Which of the following management tools gives you visibility and operational control over your AWS infrastructure?
  - [ ] CloudFormation
  - [ ] Systems Manager
  - [ ] AWS Config
  - [ ] Trusted Advisor
7. You are supporting a data processing application which runs on an EC2 instance, using gp2 storage and currently performs around 10,000 reads / writes per second. Your Sales and Marketing Teams are planning to introduce a number of additional reports which are expected to at least double the current workload for your application. How can you ensure that the performance of your application does not suffer when the new reports are introduced?
  - [ ] Upgrade to an instance type with greater CPU and memory capacity
  - [ ] Migrate all your data to DynamoDB
  - [ ] Increase the storage capacity of your gp2 volume
  - [ ] Change the storage class to Provisioned IOPS
8. You are a SysOps Administrator at a fast-growing startup that has scripted most of their infrastructure. You have a fleet of EC2 instances behind an elastic load balancer. When a new instance is launched, it performs a number of system updates before automatically copying the website's code from an S3 bucket. Due to the number of steps taken when launching a new instance, it can sometimes take up to 5 minutes for the new instance to be a fully functioning web server. This length of time is now causing a problem, as the Elastic Load Balancer reports the new instance to be unhealthy, and your autoscaling group then deletes it before it can become live. What should you do to prevent this from happening again?
  - [ ] Adjust the health check on your elastic load balancer so that an instance is considered healthy within 10 seconds of it serving HTTP traffic.
  - [ ] Pre-warm the elastic load balancer so that it can handle more requests faster.
  - [ ] Get rid of autoscaling and simply add new instances manually when you need them.
  - [ ] Reduce the number of automated steps so that the instance provisions faster and becomes healthy faster.
9. Which feature of Systems Manager can you use to run a script on multiple EC2 instances simultaneously and without logging in to each one?
  - [ ] Parameter Store
  - [ ] Maintenance Windows
  - [ ] Config
  - [ ] Run Command
10. What does the term PIOPS stand for when dealing with EBS?
  - [ ] Physical Input Output Per Second
  - [ ] Phemeral Input Output Per Second
  - [ ] Permanent Input Output Per Second
  - [ ] Provisioned Input Output Per Second
11. You have a fleet of EC2 instances in a private subnet and you need to securely access these via SSH. What should you implement?
  - [ ] An internet gateway
  - [ ] A VPN concentrator
  - [ ] A Bastion Host/Jump Box
  - [ ] A new route to your private subnet to make the subnet public
12. You have a web application that uses AutoScaling and Elastic Load Balancing. You want to monitor the application to make sure that it maintains a "good" customer experience, defined in terms of the amount of time it takes to load the application for the end-user in their browser. Which AWS CloudWatch metric can best be used for this?
  - [ ] Aggregate CPUUtilization for the web tier.
  - [ ] Aggregate NetworkIn for the web tier.
  - [ ] Latency reported by the elastic load balancer (ELB).
  - [ ] RequestCount reported by the ELB.
13. You are planning to deploy a production database to EC2 and need to choose the best storage type. You anticipate that you will need a maximum of 20,000 IOPS during peak times, but an average of 8,000 - 10,000 IOPS. What storage medium should you choose?
  - [ ] S3
  - [ ] Provisioned IOPS
  - [ ] Magnetic Storage
  - [ ] General Purpose SSD
14. What is the maximum IOPS capability of an io1 volume? (Choose 2)	
  - [ ]  80,000
  - [ ]  32,000
  - [ ]  10,000
  - [ ]  64,000
15. You are a SysOps engineer at a startup that is growing quite quickly. The startup has a fleet of EC2 instances inside an autoscaling group that scales based on CPU Utilization. You notice that CPU Utilization is not a good metric, and that the main bottleneck is the maxed-out number of connections between the ELB and an EC2 instance. You want to adjust your Autoscaling configuration to address this bottleneck. Which two of the following ELB metrics should you consider?
  - [ ] SurgeQueueLength & SpilloverCount
  - [ ] RequestCount & SpilloverCount
  - [ ] Latency & RequestCount
  - [ ] SurgeQueueLength & RequestCount
16. What is the maximum IOPS capability of a gp2 volume?
  - [ ] 23,000
  - [ ] 10,000
  - [ ] 16,000
  - [ ] 32,000
17. Which of the following ELB error codes indicates a client-side issue?
  - [ ] 500
  - [ ] 200
  - [ ] 400
  - [ ] 300
18. You are about to initiate a load test on your website to ensure it can keep up with seasonal demands. Your website is behind an elastic load balancer and will receive a burst of traffic totaling of millions of requests. What should you do to prepare for this?
  - [ ] Contact Amazon and warn them of the test. Ask them to pre-warm the elastic load balancer.
  - [ ] Use CloudFront and ElastiCache to help reduce the load.
  - [ ] Contact Amazon and ask them to build an additional data center.
  - [ ] Nothing - your Elastic Load Balancer is designed to scale.
19. Your web application runs on a group EC2 instances behind a Classic Load Balancer. This morning, users are complaining that the application is running very slowly. You suspect this is due to a significant increase in traffic to your application. Which CloudWatch metrics could you use, to determine if you are correct? (Choose 2)
  - [ ] SurgeQueueLength
  - [ ] RequestCount
  - [ ] SurgeQueueCount
  - [ ] SpilloverCount
20. Which of the following is most suitable for load balancing requests to latency sensitive production applications?
  - [ ] EC2 Load Balancer
  - [ ] Classic Load Balancer
  - [ ] Application Load Balancer
  - [ ] Network Load Balancer
21. You need to configure a load balancer with a static IP address, which of the following would you recommend?
  - [ ] Network Load Balancer
  - [ ] Classic Load Balancer
  - [ ] EC2 Load Balancer
  - [ ] Application Load Balancer
22. You are running an application on a load-balanced group of 10 EC2 instances. Which of the following metrics would use to check how many of your application servers are available?
  - [ ] HealthyInstanceCount
  - [ ] HealthyHostCount
  - [ ] RegisteredHosts
  - [ ] HTTPCode_Backend_200
23. You are a SysOps Administrator for an events company that is launching a new TV show tomorrow. You are expecting that traffic to your website tomorrow will be huge. You have created an autoscaling group and have a combination of Reserved and On-demand instances ready. You are about to contact AWS support to ask them to prewarm your ELB in order to meet this demand. Typically, AWS requires 3 pieces of information. Which of the following is NOT information that AWS requires?
  - [ ] The total size of the typical request/response that you will be handling.
  - [ ] The traffic type (HTTP or HTTPS).
  - [ ] The expected request rate per second.
  - [ ] The start and end dates of your expected surge in traffic.
24. Which of the following ELB error codes indicates a successful request?
  - [ ] 400
  - [ ] 200
  - [ ] 500
  - [ ] 300
25. You are attempting to launch a number of on-demand EC2 instances, but the launch operation fails with the InstanceLimitExceeded error. What does this error mean?
  - [ ] You have selected an instance type which does not have sufficient capacity to run the operating system
  - [ ] AWS does not currently have enough on-demand capacity available to complete your request
  - [ ] You have exceeded the default limit for the number of instances you are allowed to launch in a single region.  - [ ] Contact AWS support to have your limit increased.
  - [ ] There is a region-wide problem with EC2. Check the Personal Health Dashboard to see the status of the issue.
26. By default, how frequently are ELB metrics published to CloudWatch?
  - [ ] Every 3 minutes
  - [ ] Every 60 seconds
  - [ ] Every 5 minutes
  - [ ] Every 10 seconds
27. Which service does Systems Manager integrate with to give you visibility of the overall health of your AWS infrastructure?
  - [ ] Config
  - [ ] CloudTrail
  - [ ] Trusted Advisor
  - [ ] CloudWatch
28. You are attempting to launch a number of on-demand EC2 instances, but the launch operation fails with an InsufficientInstanceCapacity error. What does this error mean?
  - [ ] You have selected an instance type which does not have sufficient capacity to run the operating system
  - [ ] AWS does not currently have enough on-demand capacity available to complete your request
  - [ ] You have exceeded the default limit for the number of instances you are allowed to launch in a single region
  - [ ] There is a region-wide problem with EC2

### Key
1. It allows EC2 instances to download security patches from whitelisted endpoints
2. 500
3. Application load balancer
4. UnHealthyHostCount
5. Update the EBS volume where the MySQL database is running to change it's volume type from gp2 to io1. The changes will take place behind the scenes, and requires no further intervention from an administrator
6. Systems Manager
7. Change the storage class to Provisioned IOPS
8. Adjust the health check on your elastic load balancer so that an instance is considered healthy within 10 seconds of it serving HTTP traffic.
9. Run Command
10. Provisioned Input Output Per Second
11. A Bastion Host/Jump Box
12. Latency reported by the elastic load balancer (ELB).
13. Provisioned IOPS
14. 64,000, 32,000
15. SurgeQueueLength & SpilloverCount
16. 16,000
17. 400
18. Contact Amazon and warn them of the test. Ask them to pre-warm the elastic load balancer.
19. SurgeQueueLength, SpilloverCount
20. Network Load Balancer
21. Network Load Balancer
22. HealthyHostCount
23. The traffic type (HTTP or HTTPS).
24. 200
25. You have exceeded the default limit for the number of instances you are allowed to launch in a single region. Contact AWS support to have your limit increased.
26. Every 60 seconds
27. CloudWatch
28. AWS does not currently have enough on-demand capacity available to complete your request
