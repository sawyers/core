# Storage & Data Management

- [Storage & Data Management](#storage--data-management)
  - [Introduction to S3](#introduction-to-s3)
  - [S3 lab](#s3-lab)
  - [S3 lifecycle policies](#s3-lifecycle-policies)
    - [Tips](#tips)
  - [MFA delete](#mfa-delete)
    - [Tips](#tips-1)
  - [S3 encryption](#s3-encryption)
    - [Tips](#tips-2)
  - [S3 encryption lab](#s3-encryption-lab)
  - [EC2 volume types](#ec2-volume-types)
    - [Tips](#tips-3)
  - [Upgrading volume types](#upgrading-volume-types)
    - [Tips](#tips-4)
  - [Encryption and downtime](#encryption-and-downtime)
    - [Tips](#tips-5)
  - [KMS and cloud HSM](#kms-and-cloud-hsm)
    - [Tips](#tips-6)
  - [AMI's](#amis)
    - [Tips](#tips-7)
  - [Sharing AMI's](#sharing-amis)
    - [Tips](#tips-8)
  - [Snowball and Snowball edge](#snowball-and-snowball-edge)
    - [Tips](#tips-9)
  - [Storage gateway](#storage-gateway)
    - [Tips](#tips-10)
  - [Into Athena](#into-athena)
    - [Tips](#tips-11)
  - [Athena lab](#athena-lab)
  - [Introduction to EFS](#introduction-to-efs)
    - [Tips](#tips-12)
  - [EFS Lab](#efs-lab)
  - [Storage and Data Management Summary](#storage-and-data-management-summary)
  - [Quiz](#quiz)
    - [Key](#key)

## Introduction to S3

  * S3, Simple Storage Service
  * Object storage, not blocks  
  * CRUD any amount of files
  * Data is spread across multiple devices and locations
  * Basics
    * Objects (files) of 0 to 5Tb
    * Unlimited storage
    * Stored in buckets (like folders)
    * S3 is universal namespace, so names must be unique globally
    * Read after write consistency for PUTS of new objects (ready to use directly after upload)
    * Updates are eventual consistency for overwrite (time delay)
    * It is a simple key value store
      * Key (object name)
      * Value (the data)
    * Version ID
    * Metadata
    * Sub resources:
      * Bucket polices and access control lists
      * Cross origin resource sharing
      * Transfer acceleration
    * Build for 99.99% availability
    * 99.999999999% durability for S3 (11 x 9s)
    * Storage tiers are an option
    * Lifecycle management to move data across different tiers
    * Object versioning
    * Encrypting
    * Security via access control lists & bucket policies
  * Tiers
    * S3: 99.99% availability, 99.99999999999% durability across multiple devices in multiple locations and can manage the loss of 2 facilities at once
    * S3-IA (infrequent access): Rapid access but accessed less often.  General savings vs S3 but charge for access
    * S3-One Zone: same as IA but only kept in a single AZ at 20% cost savings vs S3-IA
    * Reduced redundancy storage: 99.99% durability and 99.99% availability. Good for data that can be recreated if lost. Not recommended but still available.
    * Glacier: Very cheap for very infrequently accessed objects. Has a time delay (4-5 hrs) to make objects available after request
    * Intelligent tiering
      * For unknown patterns
      * Frequent or infrequent access
      * Automatically moves data to most cost-effective tier based on how frequently you access the objects.
      * Not accessed in 30 consecutive days gets moved to IA, and moved back on access
      * No fees for access but does have a very small cost for automation, $0.0025 / 1000 objects
  * Charges
    * Storage in Gb
    * Requests made
    * Management pricing
      * Inventory, tags, analytics
    * Data management pricing
      * Transfers out of s3
    * Transfer acceleration (cloud front)
  * Tips
    * Is object based, update load files but no block access
    * 0-5tb file size
    * Unlimited storage
    * Arranged in buckets
    * Universal namespace == unique global names required
    * Read after write for PUTS of new objects
    * Eventual consistency for updates
    * Classes
      * S3
      * S3-IA
      * S3-One Zone IA
      * S3 reduced redundancy
      * Glacier
    * Core fundamentals
      * Key (name)
      * Value (data)
      * Version ID
      * Metadata
      * Sub resources - bucket-specific config
        * Policies, ACL
        * Cross origin resource sharing
    * Uploads return HTTP 200 with cli or API
    * Read the FAQ

## S3 lab

* Creating a bucket allows versioning
* Keeping logs (at a cost) in a bucket in the same region
* Lifecycle allows transitions to other storage levels or delete them
* Tags
* Object level login using cloudtrail (at cost)
* Encryption at rest using KMS key or S3 managed key
* Monitoring via Cloudwatch (at cost)
* Public access settings:
  * Default all public access is blocked
* Clicking on a file via the browser without public access you set access denied since that is considered anonymous.

## S3 lifecycle policies

* You can use this feature to manage objects so they are stored using the most effective level.
* Transitioning objects to less expensive storage levels over time, or delete them at the end of the retention period.
* Ex:
  * Transition to IA after 90 days
  * Archive to glacier after 1 year
  * Expire (delete) after 2 years
  * Server access logging can get many logs over time, so using lifecycle will help manage costs and data.

### Tips

* manage costs for objects over time
* Rules based on creation time of the object
* Can transition to different storage levels or delete the object

## MFA delete

* S3 versioning allows reverting to older versions of the object
* The object can have several versions of the object in the same bucket
* Protects from delete with an un-delete option
* You can permanently delete by providing the object Version ID in the request
* MFA delete is an extra layer of protection
  * Requires MFA code to permanently delete an object
  * Also needs MFA code to suspend / reactivate versioning on a bucket.
  * Can be the same MFA device for logging in to the account

### Tips

* Protects against unexpected deletes
* Enforces code on hard deletion or for suspend/activate versioning on the bucket

## S3 encryption

* In transit via SSL/TLS
* At rest (server side) with one of the following
  * S3 managed key
  * KMS
  * Server side encryption using customer keys
* Client Side encryption
* Enforcing encryption
  * Loading a file is via PUT request
  * If encryption at upload there is a header for it
    * x-amz-server-side-encryption: AES256 (S3 keys)
    * x-amz-server-side-encryption: ams:kms (kms keys)
  * When the parameter is included in the put it tells S3 to encryption on upload using the method set
  * Enforce this by making a bucket policy to deny any PUT that doesn't include the `x-amz-server-side-encryption` header
  
### Tips

* Encrypted in transit during the transfer
* Encrypted at rest
  * Server Side
    * SSE-S3
    * SSE-KMS
    * SSE-C (customer managed)
  * Client Side

## S3 encryption lab

* Create bucket and add policy to enforce server side encryption
  * Create new bucket
  * **Don't** enable encryption yet
  * Go to the bucket then policy generator
  * Type = S3 bucket 
  * effect = deny
  * principal = *
  * Service = S3
  * Action = PutObject
  * ARN = ARN name of bucket/*
  * Condition = StringNotEqual 
  * key = `x-amz-server-side-encryption`
  * value = aws:kms
* copy that code into the bucket policy and save
* Now when using the GUI to upload a file there is the option to set encryption during the upload. If you upload without that option the upload will fail.
* Failure is shown as forbidden

## EC2 volume types

* EBS vs Instance store (ephemeral)
* When EC2 was started all were instance store where nothing was persistent
* Later EBS launched with persistent storage
* 2 types of volumes
  * Root (where the OS lives)
  * Additional volumes, /dev/sdb
* Root devices can be either type of volume
* Instance store root max size is 10Gb
* EBS root can be between 1 to 2 Tb
* On termination EBS root are terminated by default on instance termination.
* Other EBS volumes are kept by default on termination.
* Instance store root volumes are always removed on termination
* Other instance store volumes would also be deleted automatically
* EBS are still kept by default
* Instance store backed instances can't be stopped
* Data is only kept on instance store for the life of the instance, or the failure of the underlying drive.
* Don't use anything valuable on instance store volumes. Either keep it on EBS or S3
* Instance store volumes are only good for temp data

### Tips

* Delete on termination is the default for EBS root volumes, you can set this to false only during creation
* Additional volumes persist automatically
* Instance Store doesn't persist after the instance is deleted and if used as root the instance can't be halted.

## Upgrading volume types

* So easy but may need OS commands to expand the file system
* You can encrypt devices on launch if you wish using KMS
* Volumes have to be in the same AZ as the instance
* You can change type or size on the fly with no down time
* To move around volumes you need to make a snapshot (best to reboot the instance)
* Then you can create a volume from the snap to a different AZ along with changing type / size as you wish.
* To change region you need to copy the snapshot to the desired region first. You could encrypt it during copy if you wish.
* From there you could create an image from the snap (assuming it is a boot drive) then just start that AMI

### Tips

* To swap AZ just make a snap and then make a volume in the new AZ from the snap
* To go to a different region make an AMI then copy it to the target region
* Volumes exist on EBS that are virtual HDD
* Snapshots exist in S3 (hidden)
* Snaps are PIT copy of the volume
* Snaps are incremental
* First snaps are slow because of that
* To create root snaps you should stop the instance
* You can create AMI's from both images and snapshots
* You can change EBS volumes and type on the fly
* Volumes must be in the same AZ as the instance
* To move a volume to a new AZ / Region make a snap / image then copy to target
* Snaps of encrypted volumes are encrypted automatically
* Volumes restored from encrypted snaps are encrypted
* You can share un-encrypted snapshots
  * either to specific accounts or made public

## Encryption and downtime

* For most resources you can only encrypt at creation
* EFS for example has to have a new EFS created that is encrypted them migrate data to that new resource
* RDS is similar, to encrypt you have to create a new DB and migrate the data, or use the snap+copy with encryption enabled
* EBS must be selected at creation and you can't change the status once made
  * You can move the data to an new volume with different encryption state
  * You can encrypt an existing volume by snap+copy then restore the new encrypted snap 
* S3 is more flexible
  * You can encrypt buckets or objects at any time

### Tips

* Most services need to have encryption enabled at creation time, with the exception of S3
* To change encryption mode you have to copy / migrate data to a new resource

## KMS and cloud HSM

* Both are services to create, store and manage keys to protect data in AWS
* HSM (hardware security modules) are used to protect the keys. Mostly in finance functions
* Both are highly secure
* KMS uses shared hardware as multi-tenant service
  * Manages the keys
  * Good for applications where the multi-tenant isn't a problem
  * Free-tier option
  * Always symmetric encryption (same key on both ends)
* HSM is dedicated hardware instance only for the customer
  * Not free
  * Same key functions as KMS
  * FIPS 140-2 level 3 compliance including physical tamper notice
  * Good for contractual or regulatory requirements related to dedicated hardware crypto
  * Use: DRM, PKI, auth and authorization, document signing, transaction processing
  * Symmetric (same key to encrypt as decrypt) or asymmetric (different keys)

### Tips 

* both do the same role with differences in details
* KMS is shared hardware
* If you require higher security you have to have HSM
* KMS is symmetric only, HSM is either

## AMI's

* Everything needed to launch an instance
  * A template of the root volume with OS
  * Launch Permissions for which accounts can use it, Public/private 
  * Block device mapping beyond root
* AWS provides a large selection by default
* You can also customize instances and make an AMI from that
* You have to register it before you can use it (console does that for you)
* Registered per region, if you want the image in other regions you have to copy it over

### Tips

* Templates to launch EC2
* Defaults or customized
* Region bound

## Sharing AMI's

* After creating an AMI you can keep it private, public, share it with specific accounts or sell the AMI to other users
* When shared the owner still has full control and is charged for AMI storage
* The owner must grant read permissions for the storage backing the AMI (Snapshot or S3)
* If you copy a shared AMI then you are the owner of the copy and will be charged for storage
* You can't copy an encrypted AMI shared by another account directly
  * You have to copy the snapshot and re-encrypt using your key
  * The owner must also share the snapshot and key used to encrypt
* You can't copy an AMI with a billing code (redhat, windows, etc)
* Some AMIs have a monthly charge for licenses (billingProducts)
* Launch instances using a shared AMI and create an AMI from that instance

### Tips

* They can be shared and copied across accounts with
  * Encrypted AMIs are created from copying the snapshot then re-encrypt via your own key and make an image from that
  * AMIs with billingProducts code can't be copied directly
    * You would need to launch and make a new AMI from that
  
## Snowball and Snowball edge

* It is a device used to transport tera/peta bytes of data into and out of AWS
* Makes large scale transfers fast, easy and secure
* Tamper-resistant enclosure
* 256-bit encrypted by default
* Region specific transfers, not from moving from one region to another
* You just connect it to your network
* A client manages the copy to the device
* When you finish the copy you send it back to AWS and they upload from there
* Good when you have too much data for your internet connection can't handle the transfer
  * More than 1 week to transfer over internet use snowball
* Edge
  * Each edge is 100Tb with onboard compute that can be clustered to act as a single storage and compute pool
  * Designed to do local processing and data transfer
  * S3 compatible endpoint supporting NFS and can run lambda functions as data is copied to the device
  * Buckets and Lambda functions are pre-defined before shipping
* Snowball is only data transfer
* Edge can do some pre-processing

### Tips

* Snowball is transport only
* Edge can do some simple computing along with transfer.
* Edge could cluster
* if you have days worth of data use snowball
* If you need to process as you go edge

## Storage gateway

* Gateway is an on-prem software appliance that connects with cloud storage to give seamless integration
* Supports VMware ESXi or Hyper-V
* On prem systems use it to integrate with AWS storage like S3
* Types:
  * File gateway - NFS
  * Volume Gateway -iSCSI
    * Stored volumes
    * Cached Volumes
  * Tape Gateway (VTL)
* File gateway
  * Stored as S3 objects
  * Accessed via NFS/SMB mount point
  * On-prem views it as a default file system
  * All the benefits of S3; versioning, policies, lifecycle, etc
  * Low cost option to a local SAN
  * Gateway connects to AWS via internet or direct connect
* Volume gateway
  * Cloud backed storage using iSCSI
    * Gateway stored - everything local but backup goes to AWS, low latency but you supply local storage
    * Cached - S3 is primary with local gateway acting as the cache, all in to S3 other than the cache. You only supply enough storage for that cache so lower investment in hardware
* Tape gateway
  * Tape library in glacier
  * No investment in tape infrastructure
  * Integrated with existing on-prem products

### Tips

* File gateway are flat files in s3 using nsf or smb
* Volume either caches frequent data backed by S3 or all local
* VTL backs up to glacier with or without your current backup app.

## Into Athena

* Interactive query service to analyze and query data in S3 using standard SQL
* Serverless so nothing to provision, pay per query / per Tb scanned
* No ETL 
* Mostly used to query log files like ELB, S3 access, cloudtrail logs, etc
* Generate reports based on logs
* Analyze cost and usage
* query on click-stream data

### Tips

* Interactive query using sql against log files in S3
* Serverless

## Athena lab

* Configure cloudtrail to create a named trail selecting the bucket where logs are stored, minding the region the bucket is created. Note the log file, bucket name and account ID
* Create an athena 'db' 
  * create database $NAME
* Select that database now knowing it is empty
* Create a new table with your location
```sql
CREATE EXTERNAL TABLE cloudtrail_logs (
eventversion STRING,
useridentity STRUCT<
               type:STRING,
               principalid:STRING,
               arn:STRING,
               accountid:STRING,
               invokedby:STRING,
               accesskeyid:STRING,
               userName:STRING,
sessioncontext:STRUCT<
attributes:STRUCT<
               mfaauthenticated:STRING,
               creationdate:STRING>,
sessionissuer:STRUCT<  
               type:STRING,
               principalId:STRING,
               arn:STRING, 
               accountId:STRING,
               userName:STRING>>>,
eventtime STRING,
eventsource STRING,
eventname STRING,
awsregion STRING,
sourceipaddress STRING,
useragent STRING,
errorcode STRING,
errormessage STRING,
requestparameters STRING,
responseelements STRING,
additionaleventdata STRING,
requestid STRING,
eventid STRING,
resources ARRAY<STRUCT<
               ARN:STRING,
               accountId:STRING,
               type:STRING>>,
eventtype STRING,
apiversion STRING,
readonly STRING,
recipientaccountid STRING,
serviceeventdetails STRING,
sharedeventid STRING,
vpcendpointid STRING
)
ROW FORMAT SERDE 'com.amazon.emr.hive.serde.CloudTrailSerde'
STORED AS INPUTFORMAT 'com.amazon.emr.cloudtrail.CloudTrailInputFormat'
OUTPUTFORMAT 'org.apache.hadoop.hive.ql.io.HiveIgnoreKeyTextOutputFormat'
LOCATION 's3://$BUCKET/AWSLogs/$ACCT_ID/';
```

* Create another query to search
```sql
SELECT
 useridentity.arn,
 eventname,
 sourceipaddress,
 eventtime
FROM cloudtrail_logs
LIMIT 100;
```

## Introduction to EFS

* NFS in the cloud, share a volume across multiple instances
* Shared across regions, AZ, VPC, or even on-prem
* Managed NFS so highly scalable
* Standard NFS protocol
* Lifecycle management to move to EFS IA
* Encrypted at rest and in transit as an option
* Encryption at rest can only be enabled on creation

### Tips

* HA and scalable NFS
* Good for shared config or state info
* Lifecycle management to move to IA for cost savings
* Supports encryption at transit and rest

## EFS Lab

* EFS is linux only.  Similar service for windows is FXs
* Create in a specific VPC and define mount targets in each AZ
  * Set lifecycle 
  * Set throughput, burst is normal
  * Performance mode
  * Add encryption or not.
* To mount there is a link of what to do, there is a client that has to be installed via yum / apt
* Sometimes it will timeout because of security groups allowing inbound access to EFS
  * Copy the security group ID attached to the instance
  * Add it to the default inbound rules for NFS

## Storage and Data Management Summary

* S3 is object based, you cant install apps on it
* max file size is 5tb
* unlimited storage
* files are in buckets
* bucket names are universal so must be unique across all of aws
* Read after write consistency for PUTS of new objects
* Eventual consistency for updates or deletes
* Multiple classes / tiers
  * general, s3; frequent accessed
  * IA; infrequently access pay per access
  * One Zone IA; lower redundancy 
  * Reduced redundancy storage of items that are easily replaced
  * Glacier; archived data with 3-5 hr delay to read data
* Core ideas
  * key, value, name-data
  * version
  * metadata
  * subresources from the bucket like
    * policies, acl, cors
    * transfer acceleration
  * Uploads get HTTP 200
  * Read the S3 FAQ as a reminder
  * Lifecycle policies to move objects based on creation date to other tiers or remove it
* MFA delete
  * Protect against deletion of objects
  * requires valid MFA code to delete an object
  * Or to suspend / reactive versioning
* Encryption 
  * in transit (SSL / TLS)
  * Encrypt at rest
    * Server side via SSE-S3 (AES-256) or SSE-KMS
    * SSE-C; customer managed keys
  * Client side encryption
  * You can use a bucket policy to enforce all PUTs include the server side encryption parameter
* EBS vs Instance store
  * Delete on termination is default for all EBS root
    * This can be changed at creation
  * Additional volumes persist automatically by default
  * Instance is a temp file system
    * ALWAYS deletes with the instance
* Encryption mostly needs to be enabled at creation except for S3 (bucket or object).
  * To add after the fact there will be some form of migration and likely downtime
* KMS vs. HSM
  * Both manage / generate keys
  * KMS is multi-tenancy
  * HMS is for compliance reasons where multi-tenancy is forbidden
  * HSM is FIPS level 3 standard
* AMIs give a launch template for instances
  * You can make your own from a customized instance
  * They are region bound
  * You can copy to other regions
  * They can be shared / copied around accounts
    * Encrypted AMI has to have the snapshot copied and re-encrypted using the target account key
    * Any AMI with billingProducts code that has a subscription fee.
    * You can still launch a billing product annd make an AMI from that
  * Snowball vs SN edge
    * Snowball is for transfer only
    * Edge transfers and does some light processing
    * if your data will take several days to upload then snowball is likely better
  * File Gateway
    * flat files stored on S3 and used via NFS / SMB
    * Volume gateway
      * Stored - everything local with backup to S3
      * Cached - Everything S3 with local cache
    * Tape gateway (VTL)
      * archive backups to glacier
      * with or without existing backup applications
  * Athena
    * SQL like query of logs (cloudtrail) in S3 
    * Serverless

## Quiz

1. Which of the following is true in relation to Instance Store volumes?
- [ ] The data will always be deleted when the instance is deleted
- [ ] By default it is ephemeral storage but you can configure it to be persistent at any time
- [ ] The data will still be there after the instance is deleted
- [ ] By default it is ephemeral storage but you can configure it to be persistent at volume creation time only
2. You are planning to deploy a production database to EC2 and need to choose the best storage type. You anticipate that at your busiest times, you will need a maximum of 20,000 IOPS, and an average of 8,000 - 10,000 IOPS. What storage medium should you choose?
- [ ] General Purpose SSD
- [ ] S3
- [ ] Magnetic Storage
- [ ] Provisioned IOPS
3. Which of the following statements is incorrect?
- [ ] Athena is serverless
- [ ] Athena allows you to query data in S3
- [ ] Athena is a SQL database
- [ ] Athena uses standard SQL
4. Which of the following Amazon S3 Storage Classes offer 99.999999999% (11 x 9s) durability?
- [ ] Standard, Standard-Infrequent Access, One Zone-Infrequent Access
- [ ] Reduced Redundancy Storage, Standard, One Zone-Infrequent Access
- [ ] Standard, Glacier, Reduced Redundancy Storage
- [ ] Standard-Infrequent Access, One Zone-Infrequent Access, Reduced Redundancy Storage
5. Which of the following features does S3 versioning provide? (Choose 2)
- [ ] It allows you to back up your important objects
- [ ] It allows you to store multiple versions of an object in the same bucket
- [ ] The ability to revert back to previous versions of your objects
- [ ] It appends your object name with a numerical version number
6. Which of the following strategies can be used to restrict access to data in S3?
- [ ] Create a CloudFront distribution for the bucket
- [ ] Enable IAM Identity Federation
- [ ] Set an S3 bucket policy
- [ ] Configure MFA delete
7. Which AWS service allows you to archive data located in your own data center using virtual tapes in S3 and Glacier?
- [ ] Volume Gateway - Gateway Stored
- [ ] Volume Gateway - Gateway Cached
- [ ] Backup Gateway
- [ ] Tape Gateway (VTL)
8. What is the difference between KMS and CloudHSM? (Choose 2)
- [ ] CloudHSM is multi-tenancy
- [ ] KMS allows you to have dedicated hardware
- [ ] CloudHSM allows you to have dedicated hardware
- [ ] KMS is multi-tenancy
9. Which AWS service allows you to back up data stored in your own data center as EBS snapshots stored in S3?
- [ ] Volume Gateway - Gateway Stored
- [ ] Snowball Edge
- [ ] File Gateway
- [ ] Volume Gateway - Gateway Cached
10. You are about to launch a new EC2 instance with an EBS root device volume. Which of the following statements is true? (Choose 2)
- [ ] You can disable delete-on-termination for the EBS volume when you launch the instance
- [ ] By default, if you terminate the instance, the root device will also be terminated
- [ ] If you stop the instance you will lose your data
- [ ] By default, additional EBS volumes attached to the instance will be deleted when the instance is terminated
11. You are migrating 500TB of scientific data into S3. The data also needs to be converted from EBCDIC to a stream compressed ASCII format (protobuf) format. You estimate that it is going to take over a week for the transfer if you use the spare capacity on your internet link. What should you do?
- [ ] Transform the data in-house and use Snowball to transport the data
- [ ] Upgrade your network to enable faster upload speeds and do the transform in-house
- [ ] Transform the data in-house and use CloudFront to transfer the data
- [ ] Use Snowball Edge to transform and transport the data
12. Which class of storage is most appropriate for archiving data that you need to keep but rarely need to access?
- [ ] IA
- [ ] Reduced Redundancy
- [ ] Glacier
- [ ] One Zone IA
13. You are planning to upload a set of objects to S3, which parameter can you add to the PUT request header to ensure that encryption using AWS KMS is used to encrypt your files?
- [ ] x-ams-server-side-encryption: AES256
- [ ] x-amz-server-side-encryption: aws:kms
- [ ] x-kms-server-side-encryption: AES256
- [ ] amz-x-server-side-encryption: aws:kms
14. Instance Store storage is ________.
- [ ] Persistent
- [ ] Temporary/Non Persistent
- [ ] Permanent
15. Which of the following is true in relation to a custom AMI? (Choose 3)
- [ ] You can make a custom AMI public so that any other AWS account can use it
- [ ] You can share a custom AMI with specific AWS accounts
- [ ] You cannot share an AMI with any other AWS accounts
- [ ] By default a custom AMI is private and only your own AWS account can use it
16. In addition to choosing the correct EBS volume type for your specific task, what else can be done to increase the performance of your volume? (Choose 3)
- [ ] Schedule snapshots of HDD based volumes for periods of low use
- [ ] Ensure that your EC2 instances are types that can be optimized for use with EBS
- [ ] Never use HDD volumes, always ensure that SSDs are used
- [ ] Stripe volumes together in a RAID 0 configuration.
17. Your application has a requirement for dedicated hardware to manage cryptographic keys, which service should you choose to generate, store and manage your keys?
- [ ] SSE-C
- [ ] CloudHSM
- [ ] MFA
- [ ] KMS
18. Which class of storage is most appropriate to use for storing mission critical production data?
- [ ] Standard S3
- [ ] One Zone IA
- [ ] Glacier
- [ ] Reduce Redundancy Storage
19. You are trying to copy a shared AMI which has an associated billingProducts code. What are the correct steps?
- [ ] Modify the AMI configuration file and remove the reference to billingProducts
- [ ] Ask the sharing account to remove the billingProducts code
- [ ] It is not possible to copy an AMI which contains a billingProducts code
- [ ] Launch an EC2 instance using the shared AMI and create a new AMI from the instance
20. You have enabled MFA Delete on your S3 bucket, which of the following actions will require a valid code from your registered MFA device? (Choose 2)
- [ ] Permanently deleting an object version
- [ ] Modifying S3 Lifecycle policies
- [ ] Deleting Bucket Policies
- [ ] Enabling or disabling S3 versioning
21. Which of the following services allow you to enable encryption after creation?
- [ ] S3 object or bucket
- [ ] EBS volume
- [ ] RDS database
- [ ] Elastic File System
22. You have created a custom AMI based on an instance located in eu-west-1. You have successfully used the AMI to launch instances in eu-west-1, but when you try to launch a new instance in us-east-1, you cannot see your AMI, what could be the reason for this?
- [ ] You have hit the limit on the number of AMIs you can register in us-east-1
- [ ] AMIs are regional and you haven't copied the AMI to us-east-1
- [ ] You don't have permission to use the AMI
- [ ] You cannot use an AMI that was created in a different region
23. What is Athena?
- [ ] A query service which allows you to run SQL queries on data stored in S3
- [ ] A document database backed by S3
- [ ] A query service which allows you to run Map Reduce queries on data stored in S3
- [ ] A SQL database backed by S3
24. What is the maximum size for a file stored in S3?
- [ ] 50GB
- [ ] 5GB
- [ ] 5TB
- [ ] 500GB
25. Which of the following can you achieve using S3 Lifecycle policies? (Choose 2)
- [ ] Transition objects to Infrequently Accessed storage 90 days after you created them
- [ ] Delete files if they haven't been accessed in the past year
- [ ] Delete files 5 years after creating them
- [ ] Transition files to Infrequently Accessed storage if they haven't been accessed in the past 90 days
26. Which of the following pairs of actions can best be used to restrict access to data in S3?
- [ ] Using S3 Virtual Hosting; setting an S3 ACL on the bucket or the object.
- [ ] Setting an S3 bucket policy; setting an S3 ACL on the bucket or the object.
- [ ] Creating a CloudFront distribution for the bucket; using S3 Virtual Hosting.
- [ ] Creating a CloudFront distribution for the bucket; setting an S3 bucket policy.
27. You need to implement a tiered storage system for your database backups and log files. At the end of each day, the backups need to be archived to cheaper storage but must be retained for compliance reasons. Which of the following tiered storage proposals satisfies the recovery scenario, minimizes cost, and addresses the compliance requirements?
- [ ] Use an independent EBS volume to store daily backups and copy the files to S3. Configure your Amazon S3 buckets with a lifecycle policy to archive files older than 14 days to Amazon Glacier.
- [ ] Use an independent EBS volume and daily snapshots to store the backups and log files. After 14 days, rotate your EBS snapshots.
- [ ] At the end of the day, backup your database and copy the backup files to S3. After 14 days, copy the data from S3 to Amazon RDS.
- [ ] Use Amazon EC2 ephemeral storage volumes for daily backups and log files. After 14 days, copy the backup files to Amazon EBS.
28. You have an EC2 instance which is backed by an Instance Store volume. Which of the following statements is true? (Choose 3)
- [ ] If you terminate the instance you will lose your data
- [ ] If you shut down the OS in the instance you will lose your data
- [ ] If you reboot the instance you will lose your data
- [ ] If the underlying physical disk drive fails you will lose your data
29. Your application has a requirement to generate, store and manage cryptographic keys in the cloud. There is no requirement for dedicated hardware and multi-tenancy is not an issue, which service should you choose?
- [ ] SSE-C
- [ ] MFA
- [ ] CloudHSM
- [ ] KMS
30. You need to establish an AWS backup and archiving strategy for your company. For compliance reasons, documents should be immediately accessible for 3 months and available for 5 years. Which of the following combinations of AWS services fulfills these requirements in the most cost-effective way?
- [ ] Use StorageGateway to move data to S3, then use lifecycle policies to move the data into Redshift for long-term archiving.
- [ ] Upload data to S3 and use lifecycle policies to move the aging data into Glacier for long-time archiving.
- [ ] Upload the data to an EBS volume, then use lifecycle policies to move the EBS snapshots you take to S3.
- [ ] First, use Direct Connect to upload data to S3. Then, use IAM policies to move the data into Glacier for long-term archiving.
31. You are migrating 40TB of data into S3, but you also need to process the data before transferring it to S3. Which service should you use?
- [ ] Process the data locally and use Snowball Edge to transport the data
- [ ] Use Snowball Edge to process and transport the data
- [ ] Process the data locally and use Snowball to transport the data
- [ ] Use Snowball to transfer the data to S3, then process the data using a Lambda function
32. Which AWS service allows your on-premises systems to access your files in S3 over NFS or SMB using a virtual appliance installed in your data center?
- [ ] Volume Gateway
- [ ] File Gateway
- [ ] Elastic File System
- [ ] Snowball Edge
33. Which AWS service allows you to use S3 as your primary storage and store a copy of only the most frequently accessed files locally in your own data center?
- [ ] Volume Gateway - Gateway Cached
- [ ] Elasticache
- [ ] Volume Gateway - Gateway Stored
- [ ] Cache Gateway
34. Which class of storage is most appropriate for mission-critical data that you only need to access once a year?
- [ ] One Zone IA
- [ ] Standard S3
- [ ] Reduced Redundancy
- [ ] IA
35. You are migrating 500TB of image data into S3 and you estimate that it is going to take over a week for the transfer if you use the spare capacity on your internet link. What should you do?
- [ ] Use Snowball Edge to transport the data
- [ ] Use CloudFront to transfer the data
- [ ] Upgrade your network to enable faster upload speeds
- [ ] Use Snowball to transport the data
36. Which AWS feature allows you to manage your objects to ensure that they are stored using the most cost-effective category of storage?
- [ ] Glacier
- [ ] S3 Lifecycle Rules
- [ ] Systems Manager
- [ ] Trusted Advisor
37. You are trying to copy a custom AMI which has been shared by another account. The AMI has been encrypted. What steps will you need to take to successfully copy the AMI?
- [ ] The sharing account must share the underlying EBS snapshot as well as the original encryption key used to encrypt it. Copy the EBS snapshot and re-encrypt it using your own key, then register it as an AMI
- [ ] Launch a new EC2 instance from the AMI, then use your own encryption key to create an encrypted AMI from the newly launched instance.
- [ ] The sharing account must first re-encrypt the underlying EBS snapshot with your encryption key and share it with you. Copy the EBS snapshot, then register it as an AMI
- [ ] The sharing account must copy the EBS snapshot which backs the AMI and give you an unencrypted copy which you must re-encrypt it using your own key, then register it as an AMI
38. You need to run a SQL query on your CloudTrail logs stored in S3, which service can you use to do this?
- [ ] DynamoDB
- [ ] Athena
- [ ] RDS
- [ ] Elastic Map Reduce
39. Your boss has asked you to ensure that team members use server-side encryption for any objects they upload to S3. You are planning to do this using a bucket policy. Which of the following parameters should your policy require to be present in every S3 PUT request header?
- [ ] x-amz-server-side-encryption
- [ ] amz-x-server-side-encryption
- [ ] amx-server-side-encryption
- [ ] amz-server-side-encryption

### Key

1. The data will always be deleted when the instance is deleted
2. Provisioned IOPS
3. Athena is a SQL database
4. Standard, Standard-Infrequent Access, One Zone-Infrequent Access
5. `It allows you to store multiple versions of an object in the same bucket` & `The ability to revert back to previous versions of your objects`
6. Set an S3 bucket policy
7. Tape Gateway (VTL)
8. `CloudHSM allows you to have dedicated hardware` & `KMS is multi-tenancy`
9. Volume Gateway - Gateway Stored
10. `You can disable delete-on-termination for the EBS volume when you launch the instance` & `By default, if you terminate the instance, the root device will also be terminated`
11. Use Snowball Edge to transform and transport the data
12. Glacier
13. x-amz-server-side-encryption: aws:kms
14. Temporary/Non Persistent
15. All except `You cannot share an AMI with any other AWS accounts`
16. All except `Never use HDD volumes, always ensure that SSDs are used`
17. CloudHSM
18. Standard S3
19. Launch an EC2 instance using the shared AMI and create a new AMI from the instance
20. `Permanently deleting an object version` & `Enabling or disabling S3 versioning`
21. S3 object or bucket
22. AMIs are regional and you haven't copied the AMI to us-east-1
23. A query service which allows you to run SQL queries on data stored in S3
24. 5TB
25. `Transition objects to Infrequently Accessed storage 90 days after you created them` & `Delete files 5 years after creating them`
26. Setting an S3 bucket policy; setting an S3 ACL on the bucket or the object.
27. Use an independent EBS volume to store daily backups and copy the files to S3. Configure your Amazon S3 buckets with a lifecycle policy to archive files older than 14 days to Amazon Glacier.
28. All except `If you reboot the instance you will lose your data`
29. KMS
30. Upload data to S3 and use lifecycle policies to move the aging data into Glacier for long-time archiving.
31. Use Snowball Edge to process and transport the data
32. File Gateway
33. Volume Gateway - Gateway Cached
34. IA
35. Use Snowball to transport the data
36. S3 Lifecycle Rules
37. The sharing account must share the underlying EBS snapshot as well as the original encryption key used to encrypt it. Copy the EBS snapshot and re-encrypt it using your own key, then register it as an AMI
38. Athena
39. x-amz-server-side-encryption
