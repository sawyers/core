1. You notice in the AWS management console that your EC2 instance state is FAILED. What could cause this?
  - [ ] Loss of network connectivity
  - [ ] Loss of system power
  - [ ] Incompatible kernel
  - [ ] Software issues on the physical host
2. What is the difference between a public subnet and a private subnet in a VPC?
  - [ ] The Route table in the private subnet has a route to the NAT, while the rout in the Public Subnet does not.
  - [ ] The Route table in the public subnet has a route to the internet gateway, while the route table in a private subnet does not.
  - [ ] Only ELB are allowed in the public subnet
3. You have deployed eight EC2 instances in the us-west-1a AZ and two EC2 instances in us-west-1b AZ.  You noticed that the two EC2 instances in the us-west-1b received the same amount of traffic that is load balanced between the other eight EC2 instances located in the us-west-1a AZ.  How can you fix this from the load balancer?
  - [ ] Enable cross-load balancing on your load balancer.
  - [ ] Create an ASG and configure it to balance out the instances between the AZ
  - [ ] Create 3 instances in us-west-1b and terminate 3 instances in us-west-1a
  - [ ] Migrate to an ALB
4. You have launched an amazon RDS running MySQL.  When you created the RDS instance you did not specify a maintenance window, and now you need to update the instance size from micro to large. If you request to have the update happen inside the maintenance window, what will occur?
  - [ ] Nothing. The command will be ignored until you create and apply a maintenance window.
  - [ ] Nothing. It is not possible to change the DB size using RDS
  - [ ] AWS will select and use a default maintenance window if one is not provided.
  - [ ] AWS will prompt you to provide a maintenance window when you make the request.
5. Which of the following is the customer's responsibility in the Shared Responsibility Model?
  - [ ] Restricting access to EC2 using security groups
  - [ ] Restricting physical access to AWS datacenters
  - [ ] Destroying physical media used in AWS datacenters
  - [ ] Managing updates to the Hypervisors on which instances run
6. You are tasked with storing 200gb of archival images that are requested infrequently, averaging one or two requests per image each day. Which is the most cost effective storage options for the images?
  - [ ] Amazon EBS io1
  - [ ] Amazon EBS gp2
  - [ ] Amazon S3
  - [ ] Amazon EFS
7. You need storage for your production MySQL database. The database is 19tb in size, and you will need to have ~10k IOPS – mostly writes. Without considering price, which storage option satifies the requirements?
  - [ ] Provisioned EFS 20 TB volume with 10k IOPS
  - [ ] 2 provisioned EFS 10 TB volumes with 5k IOPS
  - [ ] Provisioned EBS io1 20 TB volume with 10k IOPS
  - [ ] 2 provisioned EBS io1 10tb volumes with 5k IOPS per volume and RAID-0 striping 
8. What is the purpose of EC2 user data?
  - [ ] To install software on the EC2 instance at boot
  - [ ] To list any public keys associated with the instance
  - [ ] To show a public IP address to an EC2 instance
  - [ ] To show the localhost name for the instance
9. You have created a VPC with the CIDR of 10.0.0.0/16. You now need to divid that VPC into a public subnet and a private subnet. Which one below is a valid combination?
  - [ ] 10.1.0.0/24 & 10.2.0.0.24
  - [ ] 10.0.0.1/24 & 10.0.0.2/24
  - [ ] 10.0.1.0/24 & 10.0.2.0/24
  - [ ] 10.0.1.0/16 & 10.0.2.0/16
10. You have created an ASG with a minimum of 2 EC2 instances, a maximum of 6 instances, and a desired capacity of four instances.  Your instances take 20 minutes to launch, and they take three minutes to start once built.  How can you configure autoscaling to start and stop instances vs launching new instances from AMIs?
  - [ ] Create a new ASG configuration and configure the ASG to start the instances.
  - [ ] Edit the ASG launch configuration to start instances.
  - [ ] It is not possible, as Auto Scaling cannot stop and start instances.
  - [ ] Configure the ASG to use the AWS EC2 recovery service
11. You have a multi-AZ RDS database running MySQL. During a planned outage, how does AWS ensure that, when switching from the primary DB to the standby, it will not affect your application servers?
  - [ ] a. RDS uses elastic IP addresses that are detached from the primary database and then attached to the standby instance. This promotes the standby to be the primary.
  - [ ] b. RDS uses elastic queue service to process requests from the application servers and send them to database engines. Since this is done at the hypervisor, no user intervention is required,
  - [ ] c. RDS runs both database instances independently, and each has their own connection string. You will have to update the code on your application servers because AWS has no visibility above the Hypervisor.
  - [ ] d. RDS uses route 53 to create connection strings and will automatically update the IP address to point at the standby instance.
12. When attaching and EBS volume to an EC2 instance, what conditions must be true?
  - [ ] The EBS volume must be in the same availability zone as the instance.
  - [ ] The EBS volume must be in the same account as the instance.
  - [ ] The EBS volume must be assigned to an AMI ID
  - [ ] The EBS volume must have the same security group as the instance.
13. You've been asked to migrate a busy RDS for MySQL database to Aurora. You need to do so with little downtime and with no lost data. What is the best way to meet the above requirements?
  - [ ] Take a snapshot of the MySQL RDS instance. Use that snapshot to create an Aurora Read Replica of the RDS for MySQL. Once replication catches up, make the Aurora Read Replica into a standalone Aurora DB cluster, and point the application to the new cluster
  - [ ] Create an S3 bucket, and upload the RDS database as a flat file dump into the bucket. Restore from the dump into a new Aurora database.
  - [ ] Restore the most recent RDS automated backup to a new Aurora instance. Stop the application, point the application at the new Aurora DB instance, and start the application.
  - [ ] Take a snapshot. Restore the snapshot to a new Aurora instance. Point the application to the new Aurora DB instance, and start the application.
14. In case of a failure of the primary node of an RDS instance with RDS multi-AZ deployment, you must do the following to recover:
  - [ ] Nothing. The node will automatically fail over to each of the three included read replicas in alternative regions.
  - [ ] Nothing. The node will automatically fail over to the standby instance; a short amount of downtime may occur.
  - [ ] Manually stand up a new instance by restoring from the most recent automatic backup.
  - [ ] Manually initiate the failover using the CLI 'initialize-rds-failover' command
15. You want to monitor your web application to make sure that it maintains a good quality service for your customers which is defined by the application's page load time. What CloudWatch metric should you use to accomplish this?
  - [ ] Latency reported by the ELB
  - [ ] Request count reported by the ELB
  - [ ] Total CPU utilization for the ELB
  - [ ] Total network throughput for the ELB
16. What is evaluated by a System Status Check?
  - [ ] The host
  - [ ] The firewall
  - [ ] The VPC
  - [ ] The virtual machine
17. Your system status check has failed. What should you do to troubleshoot the issue? 
  - [ ] Stop and restart the instance.
  - [ ] Contact AWS support.
  - [ ] Terminate the instance and delete your VPC.
  - [ ] Restart the instance.
18. You are running your production database in MySQL on an independent EBS volume and you are fast approaching an average IOPS of 3000. You have decided to migrate your database to an EBS volume with provisioned IOPS. Your key users only use the database between 9 am - 6 pm, so you can afford to have some down time out of hours, but not during the working day. Which is the best option below to achieve this migration. 
  - [ ] Take a snapshot of both the root device volume and the database volume at midday. Once the snapshot is complete, terminate the EC2 instance and the database EBS volume. Restore the root device volume and EC2 instance using Provisioned IOPS SSD drives for both volumes.
  - [ ] Choose a suitable time window for your downtime. Stop the MySQL service. Take a snapshot of the EBS volume where the MySQL database is running. Detach and then delete the old database volume. Restore the snapshot to a new volume running on provisioned IOPS.
  - [ ] Choose a suitable time window for your downtime. Stop the MySQL service. Move the database to S3. Restart the MySQL service, but set the configuration so that it addresses your new bucket S3://mydatabasebucket.
  - [ ] Choose a suitable time window for your downtime. Stop the MySQL service. Take a snapshot of the EBS volume where the MySQL database is running. Detach and then delete the old database volume. Restore the snapshot to a new volume running on magnetic storage.
19. Your EBS Volume status check shows a status of "impaired". What does this mean? 
  - [ ] The instance status must be impaired. You should stop and start the instance again.
  - [ ] The volume is degraded or severely degraded.
  - [ ] The volume is stalled or not available.
  - [ ] There is insufficient data to make a reasonable diagnosis.
20. True or False: By default, EC2 monitoring carried out by CloudWatch monitors CPU, Disk, and Network & Status Checks. 
  - [ ] False
  - [ ] True
21. Which of the following is the metric used to monitor the lag between the primary RDS instance and the read replica? 
  - [ ] ReplicaQueueLength
  - [ ] ReadReplicaLag
  - [ ] ReplicaLag
  - [ ] DatabaseConnections
22. You have designed a CloudFormation script to automatically deploy a database server running on EC2 with an attached database volume. This CloudFormation script will run automatically when a predefined event takes place. The database volume must have provisioned IOPS, and cannot have any kind of performance degradation after being deployed. What should you do to achieve this? 
  - [ ] Design the CloudFormation script to use MungoDB. MungoDB is designed for performance, and is much better than any other database engine out there.
  - [ ] You should not be using CloudFormation. Instead, it would be better to script this using CodeDeploy. 
  - [ ] Test the CloudFormation script several times, and load-test it to a value matching the anticipated maximum peak load.
  - [ ] Using a combination of CloudFormation and Python scripting, pre-warm the EBS volumes after the EBS volume has been deployed.
  - [ ] Design the CloudFormation script to attach the database volume using S3, rather than EBS.
23. For custom CloudWatch metrics, what is the minimum granularity in terms of time that CloudWatch can monitor. 
  - [ ] 2 minutes
  - [ ] 1 minute
  - [ ] 5 minutes
  - [ ] 3 minutes
24. Your instance status check shows a failure, and you are unable to connect to your instance. What should you do? 
  - [ ] Stop the instance.
  - [ ] Restart the instance.
  - [ ] Raise a ticket to AWS support.
  - [ ] Terminate the instance and then delete your VPC.
25. What is evaluated during an instance status check? 
  - [ ] The weather
  - [ ] The EC2 instance
  - [ ] The VPC
  - [ ] The EC2 Host
26. You are using ElastiCache to cache your web application. The caching seems be running more and more slowly, and you want to diagnose the cause of this issue. If you are using Memcached as your caching engine, what parameter should be adjusted if you find that the overhead pool is less than 50MB? 
  - [ ] Reddis_Connections_Overhead
  - [ ] Reddis-Memory-Overhead.
  - [ ] Memcached_Connections_Overhead
  - [ ] Memcached-Memory-Overhead
27. You have a web application that uses AutoScaling and Elastic Load Balancing. You want to monitor the application to make sure that it maintains a "good" customer experience, defined in terms of the amount of time it takes to load the application for the end user in their browser. Which AWS CloudWatch metric can best be used for this? 
  - [ ] Latency reported by the elastic load balancer (ELB).
  - [ ] Aggregate CPUUtilization for the web tier.
  - [ ] Aggregate NetworkIn for the web tier.
  - [ ] RequestCount reported by the ELB.
28. You are designing a new autoscaling config group, and you need to create a new alarm to scale your EC2 instances in response to heavy web traffic. You decide to base your scaling group off an elastic load balancer metric. Which of the below would be the best metric to base this on? 
  - [ ] SurgeQueueLength
  - [ ] HTTPCode_BackEnd_4XX
  - [ ] HTTPCode_BackEnd_3XX
  - [ ] HTTPCode_BackEnd_5XX
29. You are planning to deploy a production database to EC2 and need to choose the best storage type. You anticipate that you will need 20,000 IOPS, and an average of 8,000 - 10,000 IOPS. What storage medium should you choose? 
  - [ ] Provisioned IOPS
  - [ ] S3
  - [ ] Magnetic Storage
  - [ ] General Purpose SSD
30. As your web application has increased in popularity, reports of performance issues have increased. The current configuration initiates scaling actions based on Average CPU utilization; however, during reports of slowness, CloudWatch graphs have shown that average CPU utilization remains steady at 30%. This is well below the alarm threshold of 55%. Your developers have discovered that performance degradation occurs on an instance when it is processing more than 300 threads and that this is due to the special way the application is programmed. What is the best way to ensure that your application scales to match demand? 
  - [ ] Add a script to each instance to detect the number of concurrent sessions. If the number of sessions remains over 300 for five minutes, have the instance increase the desired capacity of the AutoScaling group by one. 
  - [ ] Empirically determine the expected CPU use for 300 concurrent sessions and adjust the CloudWatch alarm threshold to be that CPU use.
  - [ ] Launch 3 to 7 additional instances outside of the autoscaling group to handle the additional load.
  - [ ] Create a custom CloudWatch metric based on a maximum allowable number of concurrent sessions, and initiate scaling actions based on that metric, instead of on CPU use.
31. Your EBS Volume status check is showing a warning. What does this mean? 
  - [ ] Your volume is degraded or severely degraded.
  - [ ] Your volume is performing as normal, but may need pre-warming.
  - [ ] There is insufficient data for a definitive diagnosis.
  - [ ] Your volume is stalled or not available.
32. A custom CloudWatch metric is required to monitor which of the following? 
  - [ ] Disk usage activity of an EBS volume attached to an Amazon EC2 instance
  - [ ] Disk usage activity of the ephemeral volumes of an Amazon EC2 instance
  - [ ] Disk full percentage of an Elastic Block Store Volume
  - [ ] CPU Utilisation of an Amazon EC2 instance
33. Your infrastructure makes use of a single t2small Nat instance within a VPC to allow inside hosts to communicate with the internet without being directly addressable.  As your traffic has grown, the amount of traffic going through the NAT has increased and is overwhelming it which is slowing down your infrastructure.  What 2 options should you do to fix this issue?
  - [ ] Add another internet gateway to your VPC
  - [ ] Increase the instance size of the NAT from t2.small to t2.medium
  - [ ] Use Direct connect to route all traffic instead.
  - [ ] Add another NAT instance and configure your subnet route tables to be spread across 2 NATS
34. True or False: With a multi-AZ RDS deployment, database snapshots taken to create read replicas are taken against the primary database. 
  - [ ] True
  - [ ] False
35. Which of the following is not a use case for read replicas?
  - [ ] Serving read traffic while the source DB instance is unavailable. If your source DB Instance cannot take I/O requests (e.g. due to I/O suspension for backups or scheduled maintenance), you can direct read traffic to your read replicas.
  - [ ] Business reporting or data warehousing scenarios; you may want business reporting queries to run against a read replica, rather than your primary DB Instance.
  - [ ] Providing greater redundancy via automatic failovers.
  - [ ] Scaling beyond the compute or I/O capacity of a single DB Instance for read-heavy database workloads. This excess read traffic can be directed to one or more read replicas.
36. In disaster recovery, what does RTO stand for?
  - [ ] Recovery Test Objective
  - [ ] Resilient Test Objective
  - [ ] Resilient Training Objective
  - [ ] Recovery Time Objective
37. You have a fleet of EC2 instances in a private subnet and you need to securely access these via SSH. What should you implement?
  - [ ] A VPN concentrator.
  - [ ] you should create a new route to your private subnet to make the subnet public.
  - [ ] A NAT
  - [ ] A Bastion Host/Jump Box
38. What is the maximum number of read replicas can you have for your MySQL database?
  - [ ] 3
  - [ ] 4
  - [ ] 5
  - [ ] 2
39. How do you force a failover from an RDS instance one AZ to an instance in another AZ?
  - [ ] Right click on the RDS instance and select "Force Failover".
  - [ ] Using the API call "RDSForceFailover".
  - [ ] By manually rebooting your RDS instance.
  - [ ] You can't force a failover. A failover will only occur if something naturally goes wrong with the AWS estate.
40. Which of the following is part of the failover process for a Multi-Availability Zone RDS instance?
  - [ ] The IP of the primary DB instance is switched to the standby DB instance.
  - [ ] The failed RDS DB instance reboots.
  - [ ] The DNS record for the RDS endpoint is changed from primary to standby.
  - [ ] A new DB instance is created in the standby availability zone.
41. Your website is evenly distributed across 10 EC2 instances in 5 AWS regions. How could you configure your site to maintain high-availability with minimum downtime if one of the 5 regions was to lose network connectivity for an extended period of time?
  - [ ] Establish VPN Connections between the instances in each region. Rely on BGP to failover in the case of a region-wide connectivity outage.
  - [ ] Create an Elastic Load Balancer to place in front of each EC2 instance. Set an appropriate health check on each ELB.
  - [ ] Create a Route 53 Latency-based Routing Record Set that resolves to an Elastic Load Balancer in each region. Set an appropriate health check on each ELB.
  - [ ] Create a Route 53 Latency-based Routing Record Set that resolves to Elastic Load Balancers in each region and has the Evaluate Target Health flag set to "True".
42. True or False: Read Replicas can have also have multiple AZs for redundancy.
  - [ ] True
  - [ ] False
43. You maintain an application on AWS that provides development and test platforms for your developers. Currently, both environments consist of an m1.small EC2 instances. Your developers notice performance degradation as they increase network load in the test environment. What should they do to remedy this situation?
    Configure Amazon Cloudwatch to provision more network bandwidth when network utilization exceeds 80%.
    Use the EBS-optimized option to offload EBS traffic.
    Add an additional ENI to the test instance.
    Upgrade the m1.small to a larger instance type.
44. You have a web application with the front end hosted on EC2 and the database hosted on RDS in a single Availability Zone. You notice that when backups are taken from your RDS instance, your applications performance is severely degraded. Your boss asks you to fix the issue. What should you do.
  - [ ] Create a multi-AZ RDS instance and migrate your DB to it. This way, when the backups are taken, they will be taken from the secondary -- not the primary.
  - [ ] Upgrade your RDS instance to an instance that has better disk IO. This way, the IO suspension from the back up will be "equaled out" by the increase in the new IO from the upgraded instance.
  - [ ] Turn off backups for RDS. This will fix the performance issue immediately.
  - [ ] Move your RDS instance to an in-house SQL server that has Netbackup installed.
45. What happens when RDS fails-over from one availability zone to another?
  - [ ] You need to contact AWS for advice as to how to set up your application in the new availability zone.
  - [ ] You need to update the connection string in your application to point to the new RDS IP address.
  - [ ] Failover is handled by AWS, and the the failover mechanism automatically changes the DNS record of the DB instance to point to the standby DB instance.
  - [ ] You don't need to do anything: applications hosted on EC2 instances will failover automatically to the same AZ to which your RDS instances have failed over.
46. You have been hired by a large online store to help optimize their web application. There are 3 webservers behind an elastic load balancer, and each connects to the same RDS instance. This RDS instance started out as a small memory optimized instance. However, as the traffic increased, the company has moved to a larger instance type. The current instance is a db.r3.8xLarge, which is the largest RDS instance currently available and it is beginning to run out of memory. You need to find a way to further scale the web application. What should you do?
  - [ ] Add a couple of read replicas and adjust the application so that read-only traffic is diverted to these instances. Write traffic will remain with the main DB server.
  - [ ] Advise the company to hold a sale, and then contact Amazon to pre-warm the elastic load balancer.
  - [ ] Advise your customer that their application has grown beyond the capabilities of AWS and should be migrated back to an on-premise solution.
  - [ ] Increase the number of EC2 web instances so you can have even more connections to the RDS instance.
47. You have created a new Auto Scaling group and you discover that your instances are not launching in to it. Which of the following is not a reason that this might be happening?
  - [ ] The Auto Scaling config is not working correctly.
  - [ ] The associated Key Pair does not exist.
  - [ ] The security group does not exist.
  - [ ] The instance type specified is not supported for Auto Scaling.
48. True or False: You can have read replicas of read replicas.
  - [ ] True
  - [ ] False
49. You are about to initiate a load test on your website to ensure it can keep up with seasonal demands. Your website is behind an elastic load balancer and will receive a burst of traffic totalling of millions of requests. What should you do to prepare for this?
  - [ ] Use CloudFront and ElastiCache to help reduce the load.
  - [ ] Nothing -- your Elastic Load Balancer is designed to scale.
  - [ ] Contact Amazon and warn them of the test. Ask them to pre-warm the elastic load balancer.
  - [ ] Contact Amazon and ask them to build an additional data center.
50. True or False: By default, you have OS-level access to Opsworks instances.
  - [ ] True
  - [ ] False
51. What are the two types of Elastic Load Balancer (Classic) sticky sessions?
  - [ ] Duration-based session stickiness and application-controlled session stickiness.
  - [ ] Application-controlled session stickiness and server-side session stickiness.
  - [ ] Server-side session stickiness and client-side session stickiness.
  - [ ] Duration-based session stickiness and server-side session stickiness.
52. You are a SysOps Administrator for an events company that is launching a new TV show tomorrow. You are expecting that traffic to your website tomorrow will be huge. You have created an autoscaling group and have a combination of Reserved and On-demand instances ready. You are about to contact AWS support to ask them to prewarm your ELB in order to meet this demand. Typically, AWS requires 3 pieces of information. Which of the following is NOT information that AWS requires?
  - [ ] The start and end dates of your expected surge in traffic.
  - [ ] The traffic type (HTTP or HTTPS).
  - [ ] The total size of the typical request/response that you will be handling.
  - [ ] The expected request rate per second.
53. You are a SysOps Administrator at a fast growing start up that has scripted most of their infrastructure. You have a fleet of EC2 instances behind an elastic load balancer. When a new instance is launched, it performs a number of system updates before automatically copying the website's code from an S3 bucket. Due to the number of steps taken when launching a new instance, it can sometimes take up to 5 minutes for the new instance to be a fully functioning web server. This length of time is now causing a problem, as the Elastic Load Balancer reports the new instance to be unhealthy, and your autoscaling group then deletes it before it can become live. What should you do to prevent this from happening again?
  - [ ] Get rid of autoscaling and simply add new instances manually when you need them.
  - [ ] Pre-warm the elastic load balancer so that it can handle more requests faster.
  - [ ] Reduce the number of automated steps so that the instance provisions faster and becomes healthy faster.
  - [ ] Adjust the health check on your elastic load balancer so that an instance is considered healthy within 10 seconds of it serving HTTP traffic.
54. True or False: You have OS level access to RDS.
  - [ ] False
  - [ ] True
55. You are a SysOps engineer at a start up that is growing quite quickly. The start up has a fleet of EC2 instances inside an autoscaling group that scales based on CPU Utilization. You notice that CPU Utilization is not a good metric, and that the main bottle neck is the maxed-out number of connections between the ELB and an EC2 instance. You want to adjust your Autoscaling configuration to address this bottleneck. Which two of the following ELB Classic metrics should you consider?
  - [ ] SurgeQueueLength & SpilloverCount
  - [ ] RequestCount & SpilloverCount
  - [ ] Latency & RequestCount
  - [ ] SurgeQueueLength & RequestCount
56. Elastic Map Reduce allows you to access the underlying operating systems of the EMR nodes.
  - [ ] True
  - [ ] False
57. A customer has a web application that uses cookie-based sessions to track logged-in users. It is deployed on AWS using Elastic Load Balancing and Auto Scaling. When load increases, Auto Scaling launches new instances, but the load on the other instances does not decrease, causing all existing users to have a slow experience. What could be the cause of the poor user experience?
  - [ ] The new instances need to be attached to an additional ELB, but they are not.
  - [ ] The ELB is continuing to send requests with previously established sessions.
  - [ ] The website uses the dynamic content feature of Amazon's CouldFront, which is keeping connections alive to the ELB.
  - [ ] The time-to-live of the ELB's DNS record is set too high.
58. AWS is responsible, by default, for implementing which of the following pairs of management-related activities in RDS?
  - [ ] Installing and periodically patching the database software; creating and maintaining automated database backups with a point-in-time recovery of up to five minutes.
  - [ ] Importing data and optimizing queries; creating and maintaining automated database backups in compliance with regulatory and long-term retention requirements.
59. Which of the following pairs of actions can best be used to restrict access to data in S3?
  - [ ] Creating a CloudFront distribution for the bucket; using S3 Virtual Hosting.
  - [ ] Using S3 Virtual Hosting; setting an S3 ACL on the bucket or the object.
  - [ ] Creating a CloudFront distribution for the bucket; setting an S3 bucket policy.
  - [ ] Setting an S3 bucket policy; setting an S3 ACL on the bucket or the object.
60. Which of the following AWS services does not have automated backups included as a standard part of the service?
  - [ ] RDS
  - [ ] ElastiCache (Redis Only)
  - [ ] EC2
  - [ ] Redshift
61. Ephemeral storage is ________.
  - [ ] Temporary/Non Persistent
  - [ ] Persistent
  - [ ] Permanent
62. You need to implement a tiered storage system for your database backups and log files. At the end of each day, the backups need to be archived to cheaper storage but must be retained for compliance reasons. Which of the following tiered storage proposals satisfies the recovery scenario, minimises cost, and addresses the compliance requirements?
  - [ ] At the end of the day, backup your database and copy the backup files to S3. After 14 days, copy the data from S3 to Amazon RDS.
  - [ ] Use an independent EBS volume to store daily backups and copy the files to S3. Configure your Amazon S3 buckets with a lifecycle policy to archive files older than 14 days to Amazon Glacier.
  - [ ] Use an independent EBS volume and daily snapshots to store the backups and log files. After 14 days, rotate your EBS snapshots.
  - [ ] Use Amazon EC2 ephemeral storage volumes for daily backups and log files. After 14 days, copy the backup files to Amazon EBS.
63. Given the following IAM policy, what does the IAM policy allow? (Choose 3): 
    ```json
    {
        "Version": "2012-10-17",
        "Statement": [ 
            { 
                "Effect": "Allow", 
                "Action": [ "s3:Get*", "s3:List*" ], 
                "Resource": "*" 
            }, 
            { 
                "Effect": "Allow", 
                "Action": "s3:PutObject", 
                "Resource": "arn:aws:s3:::corporate_bucket/*" 
            } 
        ] 
    }
    ```
  - [ ] The user is allowed to read objects from all S3 buckets owned by the account.
  - [ ] The user is not allowed to list the objects in the bucket named "corporate_bucket".
  - [ ] The user is allowed to write objects into the bucket named "corporate_bucket".
  - [ ] The user is allowed to read objects from the bucket named "corporate_bucket".
  - [ ] The user is allowed to change access rights for the bucket named "corporate_bucket".
64.  You need to establish an AWS backup and archiving strategy for your company. For compliance reasons, documents should be immediately accessible for 3 months, and available for 5 years. Which of the following combinations of AWS services fulfills these requirements in the most cost effective way?
  - [ ] Upload the data to an EBS volume, then use lifecycle policies to move the EBS snapshots you take to S3.
  - [ ] First, use DirectConnect to upload data to S3. Then, use IAM policies to move the data into Glacier for long-term archiving.
  - [ ] Use StorageGateway to move data to S3, then use lifecycle policies to move the data into Redshift for long-term archiving.
  - [ ] Upload data to S3 and use lifecycle policies to move the aging data into Glacier for long-time archiving.
65.  You have been tasked with identifying an appropriate storage solution for a 300 GB MongoDB database that requires random I/O reads of greater than 110,000 4kB IOPS. Which of the following EC2 options will meet this requirement?
  - [ ] D2 series with EBS optimized enabled.
  - [ ] R3 series with multiple IO1 disk in RAID0 and enhanced Networking.
  - [ ] C4 series with EBS provisioned IOPS and RAID10.
  - [ ] I2 series with scheduled backup.
66. You run a stateless web application with the following components: Elastic Load Balancer (ELB), 3 application servers on EC2, and 1 MySQL RDS database with 5000 Provisioned IOPS. Looking at CloudWatch, you observe 95% CPU usage on the application servers and 20% CPU usage on the database. The average number of database disk operations varies between 2000 and 2500. Response times are increasing, and users are beginning to complain. What might you do to rectifying this situation.
  - [ ] Use Auto Scaling to add additional application servers based on a CPU load threshold, and use Auto Scaling to add additional application servers based on a memory usage threshold.
  - [ ] Use Auto Scaling to add additional application servers based on a CPU load threshold, and Increase the number of open TCP connections allowed per application EC2 instance.
  - [ ] Choose an EC2 instance type for the Web/Application servers with a more appropriate CPU to memory ratio, and use Auto Scaling to add additional Web/Application servers based on a CPU load threshold.
  - [ ] Increase the number of open TCP connections allowed per application server, and use Auto Scaling to add additional application servers based on a memory usage threshold.
67. Which of the following strategies can be used to restrict access to data in S3?
  - [ ] Set an S3 bucket policy.
  - [ ] Create a CloudFront distribution for the bucket.
  - [ ] Enable IAM Identity Federation.
  - [ ] Use S3 Virtual Hosting.
68. You have an Amazon VPC with one private subnet, one public subnet, and one network address translation (NAT) server. You are creating a group of EC2 instances that configure themselves to deploy an application via GIT. Which of the following setups provides the highest level of security?
  - [ ] Amazon EC2 instances in private subnet; no EIPs; route outgoing traffic via the NAT.
  - [ ] Amazon EC2 instances in a private subnet; assign EIPs; route outgoing traffic via the internet gateway (IGW)
  - [ ] Amazon ec2 instances in public subnet; assign EIPs; route outgoing traffic via the NAT.
  - [ ] Amazon EC2 instances in public subnet; no EIPs; route outgoing traffic via the internet gateway (IGW)
69. Per the AWS Acceptable Use Policy, penetration testing of EC2 instances ________.
  - [ ] May be performed by the customer against their own instances, only if performed from EC2 instances.
  - [ ] May be performed by AWS, and is periodically performed by AWS.
  - [ ] May be performed by the customer against their own instances with prior authorization from AWS.
  - [ ] May be performed by AWS, and will be performed by AWS upon customer request.

### Partial Key

16. The host
17. Stop and restart the instance.
18. Choose a suitable time window for your downtime. Stop the MySQL service. Take a snapshot of the EBS volume where the MySQL database is running. Detach and then delete the old database volume. Restore the snapshot to a new volume running on provisioned IOPS.
19. The volume is stalled or not available.
20. True
21. ReplicaLag
22. Test the CloudFormation script several times, and load-test it to a value matching the anticipated maximum peak load.
23. 1 minute
24. Restart the instance.
25. The EC2 instance
26. Memcached_Connections_Overhead
27. Latency reported by the elastic load balancer (ELB).
28. SurgeQueueLength
29. Provisioned IOPS
30. Create a custom CloudWatch metric based on a maximum allowable number of concurrent sessions, and initiate scaling actions based on that metric, instead of on CPU use.
31. Your volume is degraded or severely degraded.
32. Disk full percentage of an Elastic Block Store Volume
33. Increase the instance size of the NAT from t2.small to t2.medium
    Add another NAT instance and configure your subnet route tables to be spread across 2 NATS
34. False
35. Providing greater redundancy via automatic failovers.
36. Recovery Time Objective
37. A Bastion Host/Jump Box
38. 5
39. By manually rebooting your RDS instance.
40. The DNS record for the RDS endpoint is changed from primary to standby.
41. Create a Route 53 Latency-based Routing Record Set that resolves to an Elastic Load Balancer in each region. Set an appropriate health check on each ELB.
42. True
43. Upgrade the m1.small to a larger instance type.
44. Create a multi-AZ RDS instance and migrate your DB to it. This way, when the backups are taken, they will be taken from the secondary -- not the primary.
45. Failover is handled by AWS, and the the failover mechanism automatically changes the DNS record of the DB instance to point to the standby DB instance.
46. Add a couple of read replicas and adjust the application so that read-only traffic is diverted to these instances. Write traffic will remain with the main DB server.
47. The instance type specified is not supported for Auto Scaling.
48. True
49. Contact Amazon and warn them of the test. Ask them to pre-warm the elastic load balancer.
50. True
51. Duration-based session stickiness and application-controlled session stickiness.
52. The traffic type (HTTP or HTTPS).
53. Adjust the health check on your elastic load balancer so that an instance is considered healthy within 10 seconds of it serving HTTP traffic.
54. False
55. SurgeQueueLength & SpilloverCount
56. True
57. The ELB is continuing to send requests with previously established sessions.
58. Installing and periodically patching the database software; creating and maintaining automated database backups with a point-in-time recovery of up to five minutes.
59. Setting an S3 bucket policy; setting an S3 ACL on the bucket or the object.
60. EC2
61. Temporary/Non Persistent
62. Use an independent EBS volume to store daily backups and copy the files to S3. Configure your Amazon S3 buckets with a lifecycle policy to archive files older than 14 days to Amazon Glacier.
63. The user is allowed to read objects from all S3 buckets owned by the account.
    The user is allowed to write objects into the bucket named "corporate_bucket".
    The user is allowed to read objects from the bucket named "corporate_bucket".
64. Upload data to S3 and use lifecycle policies to move the aging data into Glacier for long-time archiving.
65. I2 series with scheduled backup.
66. Choose an EC2 instance type for the Web/Application servers with a more appropriate CPU to memory ratio, and use Auto Scaling to add additional Web/Application servers based on a CPU load threshold.
67. Set an S3 bucket policy.
68. Amazon EC2 instances in private subnet; no EIPs; route outgoing traffic via the NAT.
69. May be performed by the customer against their own instances with prior authorization from AWS.
