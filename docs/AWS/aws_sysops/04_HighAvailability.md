
- [Elasticity & Scalability 101](#elasticity--scalability-101)
  - [Tips](#tips)
- [RDS And Multi-AZ Failover](#rds-and-multi-az-failover)
  - [Tips](#tips-1)
- [RDS & Using Read Replicas](#rds--using-read-replicas)
  - [Tips](#tips-2)
- [RDS & Using Read Replicas Lab](#rds--using-read-replicas-lab)
  - [Tips:](#tips-3)
- [RDS - What Versions](#rds---what-versions)
  - [Tips](#tips-4)
- [RDS - Encrypting RDS Snaps](#rds---encrypting-rds-snaps)
  - [Tips:](#tips-5)
- [Sharing Encrypted RDS Snapshots With Other AWS Accounts](#sharing-encrypted-rds-snapshots-with-other-aws-accounts)
  - [Tips](#tips-6)
- [Which Services Have AWS managed Maintenance Windows](#which-services-have-aws-managed-maintenance-windows)
- [Elasticache](#elasticache)
  - [Tips:](#tips-7)
- [Aurora 101](#aurora-101)
  - [Tips](#tips-8)
- [Aurora Lab](#aurora-lab)
  - [Tips](#tips-9)
- [Trouble Shooting Potential Autoscaling Issues](#trouble-shooting-potential-autoscaling-issues)
- [Cloud Front & Cache Hit Ratios](#cloud-front--cache-hit-ratios)
- [High Availability Summary](#high-availability-summary)
- [High Availability Quiz](#high-availability-quiz)
  - [Key](#key)

## Elasticity & Scalability 101

* Elasticity; expand and contract based on demand. Used for short term, like during the day
* Scalability; Long term demands on the infrastructure
* EC2
  * Scalability - increase instance sizes as required
  * Elasticity - Increase the number of instance using ASG
* DynamoDB
  * Scalability - Unlimited storage
  * Elasticity - Add IOPS for traffic spikes and decrease after
* RDS
  * Scalability - Increase instance size
  * Elasticity - Not very elastic
* Aurora
  * Scalability - Instance type
  * Elasticity - Aurora serverless

### Tips

* Consider Elasticity vs Scalability (short vs long term)

## RDS And Multi-AZ Failover

* Multi AZ keeps a copy of production DB in a separate AZ for failover. AWS manages that failover
* Updates the DNS connection endpoint for you on failover
* For disaster recovery only, not performance
* Allows an exact copy in another AZ and manages syncing to standby DB.  In an event AWS fails over with minimal ~1 minute to cut over
* MySQL, Oracle and PG users physical replication
* Multi-AZ deployments like MS SQL use logical replication
* Advantages
  * HA
  * Backups taken from secondary to avoid impact on production
  * Restores are taken from secondary for the same reason
  * You can force failover via rebooting the db

### Tips

* Not a scaling solution!
* AWS does the failover for you at the DNS endpoint
* Backup / restore are from secondary
* Read replica are used to scale
* Force failover with a reboot

## RDS & Using Read Replicas

* Use built in ability of the DB engine to make a read-only copy
* Once created the db updates on the source will be replicated using the db's built in replication options across however many replicas you created
* Used to scale beyond the compute or I/O capacity of a single DB instance for read-heavy db workloads. The excess read can be directed to read replicas
* Serving read traffic while the source db is unavailable.
* BI / data warehouse can go against replica rather than primary
* Supports MySql, PG, MariaDB
* Aurora, uses SSD backed virtual storage shared across multiples
* When creating a new read replica a snap is created
* If it is the first replica there is an I/O suspension, otherwise the snap will come from an existing replica
* Connecting to replica using a NEW DNS endpoint
* You can promote a replica to be a new stand along breaking the link to the primary

### Tips

* Up to 5 for Mysql, PG, MariaDB
* You can have replicas in different regions for all
* Replication is asynchronous only
* Read Replicas can be built off of multi-AZ
* Read replicas can also be multi-AZ
* You can have replicas of replicas but at latency risk
* Snapshots can't be taken of replicas
* Key metric is REPLICA LAG
* Understand the difference between read replicas (perf) and multi-az (HA)
	
## RDS & Using Read Replicas Lab

* Go to RDS and create a new DB, selecting MySql, picking current version and free tier, name, etc.
* After created note you can't make a read replica
* Go and change to multi AZ, knowing there is a minor performance hit because of the snapshot
* Turn back on backups, that does cause a reboot, but will enable read replicas.
* You can't have read-replicas if backup is off
* Create the replica now, it can be in any region.
* Reboot for failover, actions, reboot with failover. The UI can take time to update though. This simulates a disaster failover

### Tips:

* You can have read replicas of replicas
* Reboot with failover to switch regions
* Replicas must have backup enabled on the source before they can be created.
* This is true even if making a replica of a replica.  In that case the primary db and the first replica must both have backups enabled.

## RDS - What Versions

* Engine and version in the summary and configuration details or via CLI in db parameters, `aws rds describe-db-instances --region us-east-1` for example.

### Tips

To find the version just look or `aws rds describe-db-instances`

## RDS - Encrypting RDS Snaps

* To encrypt take a snap copy the db
* Encrypt the snap during the copy
* Restore that snap to be encrypted at rest
* On creating a db you could select to encrypt from the start
* The restore does make a NEW db as part of that
* Making a NEW database you have the option to encrypt at the start but only if you are not using the free tier.

### Tips:

* How to encrypt an existing RDS
  * Snap
  * Copy and encrypt that snap
  * Restore the snap to a new RDS instance

## Sharing Encrypted RDS Snapshots With Other AWS Accounts

* You can share snapshots that are encrypted at rest using the encryption key.
* You have to make a **custom KMS key** since it has to be shared
* Create a snap using that custom key
* Share the key to the other account
* Share the encrypted snapshot
* Restrictions:
  * Can't share encrypted snaps as public
  * Can't share Oracle or MS SQL server snaps that use transparent data encryption
  * Can't share snaps encrypted with the default KMS key

### Tips

* Share a custom KMS key and snaps created with that key with others, the default key is no good

## Which Services Have AWS managed Maintenance Windows

* Distinct from windows YOU create using tools like system manager.
* RDS, Elasticache, Redshift, DynamoDB DAX, Neptune, DocumentDB
* No Windows: EC2, Lambda, QLDB

## Elasticache

* Web service to deploy in-memory database cache in the cloud
* Can be used to greatly improve latency for read-heavy applications or compute intensive workloads like a discovery layer.
* Caching improve performance by storing data in memory for low-latency access
* Either memcached or redis (key / value store)
* Supported replication or multi-AZ with redis, memcached doesn't support multi-AZ.
* Monitor 
  * CPU use
  * Swap use (50mb or greater is a problem)
  * Evictions
  * Concurrent connections
* Elasticache is good for read-heavy databases where there isn't frequent changes
* Redshift is good for stress caused by OLAP transactions

### Tips:

* DB is under stress, elasticache is good if read heave low frequency changes
* Redshift is good for BI or OLAP (Online Analytical Processing) transactions

## Aurora 101

* Compatible with MySQL / PG to give better performance of up to 5x vs MySQL or 3x than PG at a price 1/10 of the cost of something like Oracle
* Starts with 10 gb storage, increases in 10 gb increments up to 64 tb
* Compute scales to 64vCPU and 488gb of RAM (at least)
* 2 copies are kept in each AZ with no less than 3 AZ
* Transparently handled loss of 2 copies of data for write and 3 for read
* Self healing data storage with constant monitoring and repair at the block level using a cluster volume spread across multiple AZ's with 2 copies in each AZ
* Up to 15 read replicas
* 2 types of replication 
  * Aurora (up to 15)  
  * MySQL read replicas, also up to 15
* 100% CPU 
  * Is writes the issue? Then scale up
  * Reads the problem? Scale out
* Serverless option, on-demand auto scaling Aurora with auto start/stop, scale up/down all built in, paid for by the second and you can migrate between standard and serverless

### Tips
    
* 2 flavors aurora, and serverless
* 2 copies per AZ with at least 3 AZ by default
* Self healing
* 100% CPU is scale up or out depending on writes or reads 

## Aurora Lab

* Encryption at rest is on by default, and once created all read replicas are also encrypted
* Aurora clusters are shows as an inverted tree with each instances role shown in the console.
* Failover is defined by tiers counting up from 0. 0 being highest priority, 15 being lowest
* You can modify the cluster to add reader nodes under actions
* Scale up the instance type for write bottle necks, scale out for read 
* Cross region replicas creates a new cluster in the target region. If the replication is disrupted you have to set it up again. It is recommended that you select multi-az deployment to ensure that the new cluster is also HA

### Tips

* Encryption at rest is on by default with all replicas being encrypted if the primary is
* Cross region replicas create a complete new cluster in the target region, but if the replication is disrupted you have to start over. It is recommended that you use multi-AZ to keep HA for the target cluster.

## Trouble Shooting Potential Autoscaling Issues

* What to check if instances are not launching
  * Key pair doesn't exist
  * Security group doesn't exist
  * ASG config is not working correctly
  * ASG group not found
  * Instance type not supported in the AZ
  * AZ no longer supported
  * Invalid EBS device mapping
  * ASG service isn't enabled on the account
  * Attempting to attach EBS block device to an instance-store AMI
* Test could ask for 3 possible causes

## Cloud Front & Cache Hit Ratios

* The CDN service based on the geo location. Cached to edge locations based on cache timing to keep the edge location refreshed.
* Each edge location is different than region / AZ
* Origin, source for the CDN, s3, ec2, elb, r53
* Distribution - the name of the CDN
* When connecting they get the closes edge location and check the cache. First users by default wouldn't have the origin file at the edge, so edge will DL that file and keeps a copy for the length of the keep alive
* It can be used to deliver the entire website or just parts to give the best possible performance
* 2 types:
  * Web distribution (most common)
  * RTMP (media streaming)
* Goal is to limit the number of direct requests by using more local edge locations via contents saved in cache.
* Cache hit ratio, the more from cache the better the performance of the overall distribution.
* You can see the hits, misses and errors from the CF console
* How to maximize the ratio?
  * Setting TTL
  * Caching based on query string params
  * Caching based on cookie values
  * Caching based on request headers
  * Remove accept-encoding header when compression is not needed.
  * Serving media using http
* To increase cache ratio you can configure the origin to add a cache-control max age directive to objects and set the longest practical value for max-age. The shorter the duration the more frequently CF forward a request to origin to determine if the object has changed
* Query string params are case sensitive, be consistent to better cache.
  * `Example.com?id=a1 != id=A1 != Id=a1 != ID=a1`
* Create behaviors for static and dynamic content and configure CF to forward cookies only for dynamic content.
* For example have one cache behavior for distribution and you are using that for both dynamic content like .js files and for .css files that rarely change. CF caches separate versions of your .css files based on cookie files, so each edge location forwards a request to your origin for each new cookie value or combination of cookie values.
* If you create a behavior for *.css and for which CF doesn't cache based on cookie value then CF forward to origin only for the first request that an edge receives for a given file and for the first request after a .css file expires.
* If you configure based on request headers you can improve caching if you set to forward and cache based on only request headers
* Avoid caching on headers with a large numbers of variables
* Be default when CF gets a request it checks the value of the accept-encoding header. If the value of the header contains gzip, then CF adds the header and value gzip to the cache key, then forwards it to the origin. This behavior ensures that CF serves either an object or a compressed version of the object, based on the value of the accept-encoding header. If compression is not enabled- because the origin doesn't support it, CF doesn't support it or the content is not compressible you can increase the cache hit ration by specifying different behavior.
* You can use cf to deliver on-demand video or live streaming video using any HTTP origin. One what you can set up video workflows in the cloud is by using CloudFront together with AWS media services
* Good strategies can maximize your cache hit rations
  * Setting TTL
  * Cache based on query strings, case sensitivity
  * Cookies values
  * Request headers
  * Not setting compression when not needed
  * Serving media using http

## High Availability Summary

* Elasticity and scalability, short term vs long term
* RDS Multi-AZ is not a scaling solution, it is a disaster recovery strategy
* Read replicas are used to scale
* Failover multi-AZ uses a connections string for endpoint via private DNS, during failover AWS updates that DNS to point to the fail over location, no difference on the connection string.
* Multi-AZ is disaster recovery not performance improvements
* Read Replicas can have up to 5 for Mysql, PG and maria DB, aurora can have 15 
* You can be in multiple regions for all engines
* Replication is async only
* Replicas can be build off multi-az databases and can themselves be multi-az
* You can have replicas of replicas but at the cost of latency
* Key metrics is replica lag
* Know the difference between read replicas and multi-az
* Knowing the version of engine, check the console or `aws rds describe-db-instances` 
* If you want to encrypt an existing db you have to:
  * Take a snap of the existing db,
  * Copy the snap and encrypt during the copy process
  * Restore the snap
* You can share encrypted snaps using the aes-256 if you used a custom KMS key, default key will not work, then share the key and snap encrypted with that custom key 
* Services with AWS maintenance windows include:
  * RDS
  * Elasticsearch
  * Redshift
  * DynamoDB DAX
  * Neptune
  * Amazon documentDB
* Services without AWS maintenance windows (but maybe one created by you) include:
  * EC2
  * Lambda
  * Amazon QLDB
* Elasticache has 2 options
  * Memcached
  * Redis
* Common question of what is the best service
  * Elasticache is a good choice if the db is read heavy and not prone to frequent changing.
  * Redshift is good because the db is stressed by management is running OLAP transactions (BI reports)
* Monitoring
  * CPU
  * Swap
  * Evictions
  * Concurrent connections
* Multi-AZ requires Redis
* Aurora has 2 versions
  * Normal and serverless
* Default redundancy with 2 copies of the data in 3 AZ for 6 total copies 
* Very cheap
* Storage is self healing by checking data blocks and disks continuously for errors and fixing when found
* If it hits 100% CPU then scale up if the issue is heavy writes, or scale out for heavy reads.
* Uses shared cluster storage volume
* Uses encryption at rest by default
* Failover is the lower the tier the higher the priority from 0 to 15
* Cross region replicas when creating the cross region replica if it is disrupted you have to start over so consider making the replica multi AZ for redundancy 
* ASG launch issues
  * Key pair missing
  * Security group missing
  * AS config not working
  * ASG not found
  * Instance type not supported in the AZ
  * AZ no longer supported
  * Invalid EBS mapping
  * AS service not enabled on your account
  * Attempting to attach an EBS block device to an instance-store AMI
* CloudFront cache hit ratio, the higher the better
  * Increase hit ration by setting a sane TTL for objects
  * Using consistent query parameters, case sensitive
  * Media via http
  * Cookie settings
  * Request headers
  * Not using accept-encoding for compressed objects when you can't
	
## High Availability Quiz

1. Amazon ElastiCache can fulfill a number of roles. Choose the operations from the following list which can be implemented using Elasticache for Redis. (Choose 3)
  - [ ] Relational Data Store
  - [ ] Sorted Sets
  - [ ] In-Memory Data Store
  - [ ] Pub/Sub
2. What happens when RDS fails-over from one AZ to another?
  - [ ] Failover is handled by AWS, and the failover mechanism automatically changes the DNS record of the DB instance to point to the standby DB instance.
  - [ ] You don't need to do anything: applications hosted on EC2 instances will failover automatically to the same AZ to which your RDS instances have failed over.
  - [ ] You need to update the connection string in your application to point to the new RDS IP address.
  - [ ] You need to contact AWS for advice as to how to set up your application in the new availability zone.
3. You have been hired by a large online store to help optimize their web application. There are 3 webservers behind an elastic load balancer and each connects to the same RDS instance. This RDS instance started out as a small memory optimized instance. However, as the traffic increased, the company has moved to a larger instance type. The current instance is the largest RDS instance currently available and it is beginning to run out of memory. You need to find a way to further scale the web application. What should you do?
  - [ ] Advise the company to hold a sale, and then contact Amazon to pre-warm the elastic load balancer.
  - [ ] Add a couple of read replicas and adjust the application so that read-only traffic is diverted to these instances. Write traffic will remain with the main DB server.
  - [ ] Advise your customer that their application has grown beyond the capabilities of AWS and should be migrated back to an on-premise solution.
  - [ ] Increase the number of EC2 web instances so you can have even more connections to the RDS instance.
4. You work for an online clothing retailer supporting a website running on EC2, storing product data in Aurora and product images and videos in S3. Your Marketing department announces a Black Friday sale discounting every product on the website. This drives a huge amount traffic to your website and millions of additional requests per second to your database. The CEO is concerned that performance of the website is suffering and after studying the CloudWatch data you realize that Aurora CPU utilization has hit 100%. What can you do to improve the performance of your application?
  - [ ] Increase the size of your Aurora instances
  - [ ] increase the size of your application server instances
  - [ ] Configure Aurora as multi-AZ
  - [ ] Add a read replica
5. Which of the following is part of the failover process for a Multi-Availability Zone RDS instance?
  - [ ] The failed RDS DB instance reboots.
  - [ ] A new DB instance is created in the standby availability zone.
  - [ ] The IP of the primary DB instance is switched to the standby DB instance.
  - [ ] The DNS record for the RDS endpoint is changed from primary to standby.
6. Which of the following is not a use case for read replicas?
  - [ ] Scaling beyond the compute or I/O capacity of a single DB Instance for read-heavy database workloads. This excess read traffic can be directed to one or more read replicas.
  - [ ] Providing greater redundancy via automatic failover.
  - [ ] Serving read traffic while the source DB instance is unavailable. If your source DB Instance cannot take I/O requests (e.g., due to I/O suspension for backups or scheduled maintenance), you can direct read traffic to your read replicas.
  - [ ] Business reporting or data warehousing scenarios; you may want business reporting queries to run against a read replica, rather than your primary DB Instance.
7. You work for a large telecommunications company, supporting their main customer billing application which runs on a number of load balanced EC2 instances and writes millions of records per second to an Aurora database. Last month you on-boarded a large new customer and the Billing department are now complaining about poor performance of the platform when generating customer bills which is a write-heavy operation, making multiple additional updates to the database. CloudWatch is reporting 100% CPU utilization for Aurora. What can you do to improve performance of your application?
  - [ ] increase the size of your application server instances
  - [ ] Configure Aurora as multi-AZ
  - [ ] Add a read replica
  - [ ] Increase the size of your Aurora instances
8. Which CLI command can you use to determine which version of RDS you are using?
  - [ ] describe-instances --db-version
  - [ ] describe-instances --rds-version
  - [ ] describe-db-instances
  - [ ] describe-rds-instances
9. You have a web application with the front end hosted on EC2 and the database hosted on RDS in a single Availability Zone. You notice that when backups are taken from your RDS instance, your applications performance is severely degraded. Your boss asks you to fix the issue. What should you do?
  - [ ] Move your RDS instance to an in-house SQL server that has Netbackup installed.
  - [ ] Turn off backups for RDS. This will fix the performance issue immediately.
  - [ ] Upgrade your RDS instance to an instance that has better disk IO. This way, the IO suspension from the back up will be "equaled out" by the increase in the new IO from the upgraded instance.
  - [ ] Create a multi-AZ RDS instance and migrate your DB to it. This way, when the backups are taken, they will be taken from the secondary -- not the primary.
10. You are using ElastiCache to cache your web application. The caching seems to be running more and more slowly, and you want to diagnose the cause of this issue. If you are using Memcached as your caching engine, what parameter should be adjusted if you find that the overhead pool is less than 50MB?
  - [ ] Memcached-Memory-Overhead
  - [ ] Redis_Connections_Overhead
  - [ ] Redis-Memory-Overhead.
  - [ ] Memcached_Connections_Overhead
11. Which of the following features only relate to Spread Placement Groups?
  - [ ] The placement group can only have 7 running instances per Availability Zone
  - [ ] Instances must be deployed in a single Availability Zone
  - [ ] The name of your placement group must be unique within your AWS Account
  - [ ] There is no charge for creating a placement group
12. You are attempting to launch EC2 instances in an auto-scaling group, however every time you try, the launch operation fails. Which of the following could be a reason for the failure? (Choose 3)
  - [ ] The Security Group specified in the launch configuration doesn't exist
  - [ ] The requested instance type is not supported in your Availability Zone
  - [ ] The Key Pair you have specified doesn't exist
  - [ ] You have hit the default limit for the number of times you can use the Key Pair

### Key
1. Sorted sets, in-memory data store, pub/sub
2. Failover is handled by AWS, and the failover mechanism automatically changes the DNS record of the DB instance to point to the standby DB instance.
3. Add a couple of read replicas and adjust the application so that read-only traffic is diverted to these instances. Write traffic will remain with the main DB server.
4. Add a read replica
5. The DNS record for the RDS endpoint is changed from primary to standby.
6. Providing greater redundancy via automatic failover.
7. Increase the size of your Aurora instances
8. describe-db-instances
9. Create a multi-AZ RDS instance and migrate your DB to it. This way, when the backups are taken, they will be taken from the secondary -- not the primary.
10. Memcached_Connections_Overhead
11. The placement group can only have 7 running instances per Availability Zone.
  * Spread placement groups have a specific limitation that you can only have a maximum of 7 running instances per Availability Zone and therefore this is the only correct option. Deploying instances in a single Availability Zone is unique to Cluster Placement Groups only and therefore is not correct. The last two remaining options are common to all placement group types and so are not specific to Spread Placement Groups. Further information: https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/placement-groups.html
12. The Security Group specified in the launch configuration doesn't exist
  * The requested instance type is not supported in your Availability Zone
  * The Key Pair you have specified doesn't exist
