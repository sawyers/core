- [Introduction](#introduction)
  - [Exam tips](#exam-tips)
- [Monitor & modify EBS](#monitor--modify-ebs)
- [ELB](#elb)
  - [Access Logs](#access-logs)
  - [Request tracing](#request-tracing)
  - [CloudTrail](#cloudtrail)
  - [Tips](#tips)
- [Monitoring Elasticache ](#monitoring-elasticache-)
- [Metrics from Multiple regions & custom dashboards](#metrics-from-multiple-regions--custom-dashboards)
- [Creating a billing alarm](#creating-a-billing-alarm)
- [AWS organisations lab](#aws-organisations-lab)
  - [Tips](#tips-1)
- [Resource groups and tagging](#resource-groups-and-tagging)
- [Cost explorer and cost allocation tags](#cost-explorer-and-cost-allocation-tags)
- [EC2 pricing models](#ec2-pricing-models)
- [Config 101](#config-101)
- [Config lab](#config-lab)
- [Config vs CloudTrail vs CloudWatch](#config-vs-cloudtrail-vs-cloudwatch)
- [Health dashboards](#health-dashboards)
- [Monitoring and reporting summary](#monitoring-and-reporting-summary)
- [Quiz](#quiz)
  - [Key:](#key)
  
## Introduction
It is a monitoring service of resources and apps. 
  * Compute:
    * ASG
    * ELB
    * Route 53
  * Storage & CD:
    * EBS volumes
    * Storage Gateways
    * CloudFront
  * Databases:
    * RDS, elasticservice, etc
  * Other:
    * SNS
    * OpsWorks
    * Estimated Charges

On EC2 it monitors host level metrics
  * CPU
  * Network
  * Disk
  * Status 

Other data can be reported on as custom metrics. By default monitoring is every 5 minutes but detailed is every minute which is as frequent as possible.  

Data can be read using API's and by default the retention time is forever.  You can change retention for each log group at any time. That includes post termination of an instance.

You can set and trigger alarms on anything from cloudwatch.

### Exam tips

CloudWatch is a monitoring service to monitor your AWS resources, as well as the applications that you run on AWS.

Host level metrics are
  * Cpu
  * Disk IO
  * Network
  * Status

Other items need custom metrics

  * Metrics go as fast as per minute, but no faster

Monitoring ec2 w/ custom metrics

  * Cloudwatch can be used on prem by downloading and installing SSM agent and Cloudwatch agent.

Create a role with grants to use cloudwatch
Role
  * Ec2
  * CloudwatchFullAccess (overly broad)
        
    
Now creating an instance with that role attached along with the following user_data 

```bash
#!/bin/bash

yum update -y

sudo yum install -y perl-Switch perl-DateTime perl-Sys-Syslog 
perl-LWP-Protocol-https perl-Digest-SHA.x86_64

cd /home/ec2-user/

curl https://aws-cloudwatch.s3.amazonaws.com/downloads/CloudWatchMonitoringScripts-1.2.2.zip -O

unzip CloudWatchMonitoringScripts-1.2.2.zip

rm -rf CloudWatchMonitoringScripts-1.2.2.zip

#   Use the commands below for the lab.
#   /home/ec2-user/aws-scripts-mon/mon-put-instance-data.pl --mem-util --verify --verbose
#   /home/ec2-user/aws-scripts-mon/mon-put-instance-data.pl --mem-util --mem-used --mem-avail
#   */1 * * * * root /home/ec2-user/aws-scripts-mon/mon-put-instance-data.pl --mem-util --mem-used --mem-avail
```

So again, you always get host level metrics but nothing from inside the instance.  To get anything from inside the instance you need to use custom metrics and you may or may not need detailed monitoring to get more frequent metrics, but never faster than per minute interval.

Even if you gather custom metrics at 1 minute intervals it will still be aggregated to 5 minutes in cloudwatch if you don't have detailed metrics enabled

## Monitor & modify EBS

Four current types:

Type | Use Case
:--- | :---
General purpose (SDD) - **gp2** | Any, default storage
Provisioned IOPS (SDD) - **io1** | Critical apps with large workloads or are otherwise IO bound; 10k IOPS or more
Throughput Optimized (HDD) - **st1** | Streaming workloads, big data / log processing; can't be boot volume
Cold (HDD) - **sc1** | Large but infrequently accessed data where low cost is important; can't be boot volume
    
All volumes go up to 16 TiB

GP2 has a base of 3 IOPS/Gb with a max of 10k IOPS

You can, at most burst up to 3,000 IOPS for 30 minutes but if you need more IOPS you need a larger volume. If you need beyond 10,000 IOPS then you must use **io1**.

100Gb volume gets 300 IOPS but can burst up to 3k at a cost of 2700 IOPS credits

But if you need between 3k and 10k you have to increase the volume size (1tb is the cutoff)

IO credits gets a base of 5.4 mill credits and you earn credits when not bursting.  The max credits allows 30 minutes max burst.

You use to need to warm up EBS, but that is no longer true.  But blocks restored from snapshots do need to access the block from it to be written out to the volume.  In production you can just read from all blocks of the restored volume to get max performance directly after restore of the snapshot.  There is a whitepaper related to it

Important metrics:
  * **Volume read / write IOPS** are the key metrics, in seconds.
  * **Volume queue length**; pending IO, the larger the queue the worse the congestion, should be at or close to 0 
  * **Status checks** ok || warning (degraded) || impaired || insufficient data

You can modify the type on the fly with current gen.  You can adjust size, type, or for io1 IOPS via either console or CLI.  On size modify extend the FS in the host as needed.

Tips:
  * Remember the 4 types of storage; **General Purpose** (SDD) - gp2, **Provisioned** IOPS (SDD) - io1, **Throughput Optimized**** (HDD) - st1, **Cold** (HDD) - sc1
  * Use cases: 
    * gp2 - virtual desktops, dev/test, boot volume, low-latency apps
    * io1 - Large db workloads
    * st1 - big data warehouses, streaming workloads, can't be boot
    * sc1 - infrequent access where cost is more important than performance, can't be boot
  * Track your metrics for R/W IOPS and queue length in CloudWatch

## ELB

* Application load balancer 
* Network load balancer
* Classic load balancer

Most common type is application LB, classic is being deprecated over time.

Monitoring via
  * CloudWatch metrics
  * Access logs
  * Requests logs
  * CloudTrail logs
    
CloudWatch == performance
CloudTrail == auditing of API calls in AWS

ELB publishes data to cloudwatch for load balancers and targets and to retrieve stats about those data points as metrics.  The metric is a point in time value.

Create a balancer from the ec2 section, not that classic is there but grayed out. Create a classic and add the test instance to the balance group

### Access Logs

ELB provides access logs that capture detailed information about requests sent to your load balancer. Each log contains information such as the time the request was received, the client's IP address, latencies, request paths, and server responses. You can use these access logs to analyze traffic patterns and troubleshoot issues. Access logging is an  optional feature of ELG that is disabled by default. After you enable access logging for your load balancer, ELB captures the logs and stores them in an S3 bucket that you specific as compressed files. You can disable access logging at any time.

Logs can be very large in production and are most easily read using Athena or other 3rd party tools like sumo logic.

**IMPORTANT** - Access logs store data where the EC2 instance has been deleted. For example if you have a fleet of instances behind an ASG. For some reason your application has a load of 5XX errors where is only reported by your end customers a couple of days after the event. If you aren't storing the web server logs in a persistent location it is still possible to trace these 5XX errors using access logs stored in S3.

### Request tracing

You can use request tracing to track HTTP requests from clients to targets or other services. When the load balancer receives a request from a client, it adds or updates the X-Amzn-Trace-Id header before sending the request to the target. Any services or applications between the load balancer and the target can also add or update this header. **Only on Application Load Balancers**

### CloudTrail

You can use CloudTrail to capture detailed information about the calls made to the ELB API and store them as log files in S3. From these logs you can find where the calls were made, the calling IP, who made the call, when it was made, etc.

### Tips

CloudWatch == performance
CloudTrail == auditing of API calls in AWS
4 ways to monitor ELB; CloudWatch, CloudTrail, Access logs, Request tracing (ALB only)
Access logs last even when the instance has been deleted

## [Monitoring Elasticache ](https://docs.aws.amazon.com/AmazonElastiCache/latest/red-ug/CacheMetrics.html)

Caches popular database contents using memcached or redis; 4 items to monitor:
1. CPU use
  * Memcached is multi-threaded and can handle loads up to 90%, **beyond that more nodes are needed**
  * Redis is not multi-threaded so to find the scale point take 90 and divide by the number of cores. For example if you are using m1.xlarge with 4 cores that would be 22.5% load amount to add more 
2.  Swap Use
  * Swap us is the amount of used from the paging file.  Swap is the size of RAM in general
  * Memcached should be around 0 most of the time and should not go past 50Mb. **If it goes beyond increase the memcached_connections_overhead parameter.**
  * memcached_connections_overhead defines the amount of memory to be reserved for memcached connections and other overhead.
  * Redis doesn't use SwapUsage as a metric, instead it uses reserved-memory
3. Evictions
  * A FIFO queue that ages out items when new items are added and there is no free space for the new item
    * Memcached
      * There is no default recommendation, either scale up or out
    * Redis
      * There is no default recommendation, scale out as needed
4. Concurrent Connections
  * Both has no recommended setting, pick a threshold based off your application. 
  * If there is a large and sustained spike in concurrent connections it can mean a large traffic spike or your app isn't release connections as it should be.  **Set an alarm on the number of concurrent connections for elasticache.**

Exam tips
  * Elasticache is 2 different engines, **memcached** or **redis**
    * Monitor cache engines with:
      * CPU use
      * Swap Use
      * Evictions
      * Concurrent connections

## Metrics from Multiple regions & custom dashboards
  * Create new dashboard from CloudWatch
  * Add ec2 metrics as line graphs to see instance resource use.
  * When you add widgets to a dashboard remember to save it.
  * You can add metrics to a dashboard from multiple regions
  * To add widgets you need to be in the correct region, but once you have done that you don't need to worry about it further.

## Creating a billing alarm

  * From CloudWatch under billing click create alarm
  * Pick a max value to trigger the alarm, 10 USD
  * Create a new SNS topic 'BillingAlarm'
  * Select to send the alarm to email, then confirm that email 
  * In the exam on how to know when you are over a set amount of billing for your account.

## AWS organisations lab

  * Allows management of multiple accounts at once creating a group of accounts that you can apply policies to these groups. 
  * Central managed policies across accounts
    * Create groups of accounts then attach policies to a group to be sure that the correct policies are applied across the accounts.  This allows centralized policies without needing custom scripts or manual processes.
  * Control access to aws services
    * Create service control policies to allow or deny services to a specific group even if it is allowed in IAM. SCP will override IAM settings to control services at the account level.
    * Policies are attached to each organization and that is inherited by the accounts under that org.  
  * Automate account creation
    * You can provision an account into an Org.  The organizations APIs allow creating new accounts programmatically and to add the new accounts to a specific group.  The policies attached to that group are then automatically applied to the new account. 
  * Manage billing
    * Single billing method for all groups in the organization through consolidated billing along with discounts for volume purchases across all accounts in the organization.
  * Setup:
    * Search for organizations
    * Create new organization under the root like dev, production, hr etc.
    * Creating policies are as for IAM, select a service, then subset and apply.  Multiple services can be selected for a single policy of course.
    * Once created you simply attach the policy(s) to the units as needed. 

### Tips
  * Central management of policies across multiple accounts
  * Control access to services using Service Control Policies (SCP)

## Resource groups and tagging

  * Key value pairs attached to resources and can be inherited from other creation methods like EBS, auto scaling, CloudFormation, etc.
  * Resource groups allow resources grouped where one or more  tags are common.
  * Tags are case sensitive
  * Resource groups are region by region.
    * Create a tag based group
    * Resource type
    * Give the group a name
    * You could tag in region by group (perf, qa, dev, etc) or use or by owner
    * Mostly used via Systems manager tool. Which can use the saved groups to execute automation on all instances in the group (stop all perf machines in one go for example) and how the changes are applied, rolling, manual, one by one, etc.  You can also set maintenance windows by group.
  * Tag everything and you can group tags via resource groups and use systems manager to automate tasks across groups.
  * Resource groups are region specific, either tag or CloudFormation based
  * Also used for System Manager via resource groups
    
## Cost explorer and cost allocation tags

  * Uses tags to view and analyzed costs and usage via reports or graphs.
  * You can view up to the last 13 months and forecast costs for up to 3 months in the future.
  * After applying tags to resource and active the tags in the billing and cost console a generated report as CSV will be created and allow group by tags.
  * Frequent questions, make sure you tag your resources
  * Configure tags by cost centers
  * You have to activate cost allocation tags so you can generate reports based on them
    
## EC2 pricing models

  * On demand, low cost no up front or long-term commitments that shouldn't be interrupted
  * Reserved, steady state use or need reserved capacity at a great discount but at an up front price
  * Convertible RI's can have attributes of the RI changed as long as the exchange creates an RI of equal or greater value
  * Scheduled RI's are available during a time window you reserve to match reservations to a predictable schedule where the resource is only needed a fraction of a day week or month.
  * Spot are for flexible start / end times or for urgent use of large capacity or need very low compute price.  Select a bid price that you are willing to pay (bid) and as long as the spot price is lower than your bid you get resources.  If spot goes over bid you loose the instanced
  * Dedicated are for regulated requirements (full server) with no other customers installed on the hardware. Can be purchased on-demand or reservation, may be required for licensing

## Config 101

  * Fully managed service to provide resource inventory, config history and config change notifications to enable security and governance.
  * Enables: Audit over time, do security analysis, resource tracking
  * Provides: config snapshots and logs config changes in AWS.
  * Setup by region currently
  * Works similar to cloudtrail, as soon as a change is made config catches the event and stores it to S3 then could trigger a target (lambda with custom or standard rules). Lambda only reports if it is or isn't in compliance and when non-complaint sends SNS message.
  * Key components:
    * Dashboard
    * Config rules
      * Managed
      * Custom
    * Resources
    * Settings
    * Terms:
      * **Configuration items**: Point in time attributes of resource
      * **Configuration snapshots**: collection of config items
      * **Configuration streams**: streams of changed items
      * **Configuration history**: collection of items over time
      * **Configuration recorder**: what stores things in s3 and notifies via SNS, region specific
    * Can see:
      * Resource type
      * Resource id
      * Compliance
      * Timeline
        * Config details
        * Relationships
        * Changes
        * Cloudtrail events
      * Checks
        * Trigger
          * Periodic
          * Config snapshot delivery
        * Managed rules
          * ~40 rules
          * Basic but complete
          * Can also make custom rules.

## Config lab

  * Create and applied a basic ssh check on security groups
  * Trigger on change or every so often
  * Needs IAM with read permissions to recorded resources, s3, SNS
  * Restrict access to this by IAM to keep it a good audit use, only admins
  * Config can work with CloudTrail via config
  * Is a feature with cost per check per run. The unit price is minor but can add up in time.

## Config vs CloudTrail vs CloudWatch

  * CloudWatch monitors performance metrics or cost alerts
  * CloudTrail monitors API calls to AWS
  * Config records the state of the AWS environment and give notice of changes over time.

## Health dashboards
 
  * Consist of service health dashboards of the services as a whole per region.
  * Personal health are alerts specific to you

## Monitoring and reporting summary

  * CloudWatch monitors service to monitor resources as well as the applications that are run on AWS
  * Host level metrics of CPU, network, disk and status
  * RAM or other items are custom metrics
  * Custom min granularity is 1 minute, std is 5 minutes but faster than 5 minutes required detailed monitoring on the resource.
  * Terminated instances/ELB can be retrieved after termination and logs are stored forever
  * Can be used on prem via SSM and CloudWatch agents
  * 5 types of EBS:
    *  General purpose (SSD)
    *  Provisioned IOPS (SSD)
    *  Throughput optimized HDD
    *  Cold HDD
    *  Magnetic (legacy)
  * Can burst up to 3000 IOPS, if you need between 3k and 10k increase the volume size to get more, otherwise you must use PIOPS
  * CloudWatch monitors performance
  * CloudTrail monitors API calls in AWS platform
  * ELB monitoring
    * CloudWatch metrics
    * Access logs
    * Request tracing (ALB only)
    * CloudTrail logs
  *  Access logs can store data where the instance has been deleted, so if you scale up and the app dies and you find out later you can still trace the errors in access logs via S3.  You can also use Athena to query the logs
  *  Elasticache is either memcached or redis to cache most current database results and is monitored via:
    * CPU use
    * Swap use ( matches RAM)
    * Evictions
    * Concurrent connections
  * CloudWatch dashboards are multi-region and can add any widget from specific regions, but remember to save at the end
  * Billing alarms alert when you go over a pre-set cost for the month.
  * Organizations allows policies across accounts, control access to services, automate account creation and management, consolidate billing across multiple accounts for bulk purchase discounts.
  * Resource groups, needs everything tagged to allow grouping and to have systems manager to automate tags across resource groups.  This is regional.
  * Ec2 are:
    * **On demand**, fixed time rate
    * **Reserved**, discounts but up front cost
    * **Spot**, super cheap but can be terminated at any point depending on changing price
    * **Dedicated**, physical server for licenses requirements
  * Compliance checks
    * Triggers
      * Periodic
      * On change
    * Managed rules
      * ~70+ and growing
    * Needs IAM with read only permissions to recorded resources, write to S3 logging bucket and SNS.
    * Should be restricted to admins only for full access to keep audit clean
    * CloudTrail would track if something is turned off
  * CloudWatch vs CloudTrail vs config
    * CloudWatch is performance
    * CloudTrail is API logging
    * Config is audit / history of AWS environment
  * Health dashboards are either global or personal to alert of issues being seen in AWS. Global may be things like Route 53 is having issues in a specific region. Personal may be that one of your instances is running on hardware scheduled for replacement.
    
## Quiz

1. By default, EC2 monitoring carried out by CloudWatch monitors which metrics? Pick 3
  - [ ] CPU
  - [ ] Disk
  - [ ] Memory
  - [ ] Status
2. Which of the following services can you use to monitor API calls in AWS?
  - [ ] CloudTrail
  - [ ] Trusted Advisor
  - [ ] Systems Manager
  - [ ] CloudWatch
3. Which of the following services can you use to monitor performance metrics in AWS?
  - [ ] Systems Manager
  - [ ] Trusted Advisor
  - [ ] CloudWatch
  - [ ] CloudTrail
4. Which AWS service allows you to audit the configuration of your AWS environment, provides a resource inventory and can e used to notify you of configuration changes?
  - [ ] Systems Manager
  - [ ] CloudTrail
  - [ ] AWS config
  - [ ] CloudWatch
5. A custom CloudWatch metric is required to monitor which of the following?
  - [ ] CPU utilization of an EC2 instance
  - [ ] Disk usage activity of the ephemeral volumes of an instance
  - [ ] Disk usage activity of an EBS volume attached to an instance
  - [ ] Disk full percentage of an EBS volume
6. Which of the following CloudWatch metrics can you use to determine the percentage of I/O operations delivered to the total IOPS provisioned for an EBS volume?
  - [ ] VolumeThroughputPercentage
  - [ ] IOThroughputPercentage
  - [ ] VolumeConsumedReadWriteOps
  - [ ] ThroughputConsumedPercentage
7. Your data analytics team wants to run a number of data processing jobs in parallel. All processed data will be written to an RDS database and the developers have indicated that it doesn't matter if the jobs stop and restart.You have a number of days to produce the data. Which is the most cost-effective way to purchase compute instances to run these jobs?
  - [ ] Dedicated hosts
  - [ ] Spot instances
  - [ ] On-Demand
  - [ ] Reserved instances
8. You are running your mission-critical application on a large number of On-Demand instances and your monthly bill is steadily growing each month. Your CFO challenges the project to reduce costs by 50% over the next 3months. What can you suggest to optimize your infrastructure costs?
  - [ ] Reserved instances
  - [ ] Dedicated hosts
  - [ ] Spot instances
  - [ ] Consolidate your applications to fewer larger instances and terminate some of your instances
9. Which of the following services is used for monitoring AWS resources as well as the applications you run on AWS?
  - [ ] Systems manager
  - [ ] X-Ray
  - [ ] CloudTrail
  - [ ] CloudWatch
10. Which of the following CloudWatch metrics would be most useful in diagnosing a suspected I/O issue on your EBS volume?
  - [ ] VolumeIdleTime
  - [ ] VolumeQueueLength
  - [ ] IOWaitTime
  - [ ] SurgeQueueLength
11. Which service allows you to manage multiple AWS accounts at once, automate account creation, control access to AWS services and consolidate billing across multiple accounts?
  - [ ] Trusted Advisor
  - [ ] AWS Organizations
  - [ ] IAM
  - [ ] AWS Billing Dashboard
12. Which feature allows you to organize your AWS resources according to user-defined tags?
  - [ ] Security Groups
  - [ ] AWS Organizations
  - [ ] IAM Groups
  - [ ] Resource groups
13. As your web application has increased in popularity, reports of performance issues have increased. The current configuration initiates scaling actions based on the Average CPU utilization, however, during reports of slowness,CloudWatch graphs have shown that average CPU utilization remains steady at 30%. This is well below the alarm threshold of 55%. Your developers have discovered that performance degradation occurs on an instance when it is processing more than 300 threads and that this is due to the special way the application is programmed. What is the best way to ensure that your application scaled to match demand?
  - [ ] Empirically determine the expected CPU use for 300 concurrent sessions and adjust the CloudWatch alarm threshold to be that CPU use.
  - [ ] Launch 3 to 7 additional instances outside of the auto scaling group to handle the additional load
  - [ ] Add a script to each instance to detect the number of concurrent sessions. If the number of sessions remains over 300 for five minutes, have the instance increase the desired capacity of the auto scaling group by one
  - [ ] Create a custom cloudwatch metric based on a maximum allowable number of concurrent sessions, and initiate scaling actions based on that metric, instead of on CPU use.
14. For which of the following would you need to use a custom metric in order to monitor it in Cloudwatch?
  - [ ] CPU
  - [ ] Memory
  - [ ] Network
  - [ ] Disk
15. You have a number of application servers behind an Application load balancer, which of the following is a way of monitoring HTTP requests from users of your application?
  - [ ] Cloudwatch metrics
  - [ ] Cloudtrail logs
  - [ ] Access logs
  - [ ] Request tracing
16. You have a number of application servers behind an elastic load balancer and your security team is requesting that you provide detailed information for every request received by the load balancer, including client IP address and server responses. They would like these logs to be stored in an S# bucket for future use. Which service can you use to provide this?
  - [ ] Access logs
  - [ ] Cloudtrail logs
  - [ ] Request tracing
  - [ ] Cloudwatch metrics
17. For custom cloudwatch metrics, what is the minimum granularity in terms of time that cloudwatch can monitor
  - [ ] 1 minute
  - [ ] 2 minutes
  - [ ] 5 minutes
  - [ ] 3 minutes
18. Your application is running slowly and you notice the number of evictions on your elasticache cluster is steadily increasing, what should you do?
  - [ ] Migrate to redis
  - [ ] Scale your elasticache cluster
  - [ ] Scale your load balancer
  - [ ] Scale your application servers
19. Your application is using elasticache to handle session state and cache frequently accessed data, however during peak times users are complaining that your website is running very slowly. You check the cloudwatch metrics for your application servers and database and cannot see any evidence of an issue, however you notice that yourMemcached cluster is showing 98% CPU utilization. What can you do to improve performance?
  - [ ] Scale your application server by adding more EC2 instances
  - [ ] Scale your cluster by adding more CPU capacity
  - [ ] Scale your cluster by adding more nodes
  - [ ] Scale your cluster by adding read replicas

### Key:
    1. CPU, Disk, Status
    2. CloudTrail
    3. CloudWatch
    4. AWS Config
    5. Disk full percentage of an EBS volume
    6. VolumeThroughputPercentage
    7. Spot instances
    8. Reserved instances
    9. CloudWatch
    10. VolumeQueueLength
    11. AWS Organizations
    12. Resource groups
    13. Create a custom cloudwatch metric based on a maximum allowable number of concurrent sessions, and initiate scaling actions based on that metric, instead of on CPU use.
    14. Memory
    15. Request tracing
    16. Access logs
    17. 1 minute
    18. Scale your elasticache cluster
    19. Scale your cluster by adding more nodes
    
