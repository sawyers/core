# Additional Topics

- [Additional Topics](#additional-topics)
  - [Service catalog](#service-catalog)
    - [Tips:](#tips)
  - [Policy wildcards](#policy-wildcards)
    - [Tips:](#tips-1)
  - [CloudFront errors](#cloudfront-errors)
    - [Tips:](#tips-2)
  - [Multi-Account Access To Direct Connect](#multi-account-access-to-direct-connect)
    - [Tips](#tips-3)
  - [Inter-Region VPC Peering](#inter-region-vpc-peering)
    - [Tips](#tips-4)
  - [HTTPS & Storing SSL Certificates](#https--storing-ssl-certificates)
    - [Tips](#tips-5)
  - [CloudFormation Best Practices](#cloudformation-best-practices)
    - [Tips](#tips-6)
  - [CloudFormation Failed Rollback](#cloudformation-failed-rollback)
    - [Tips](#tips-7)
  - [Additional Resources To Help You Prepare For The Exam](#additional-resources-to-help-you-prepare-for-the-exam)
    - [Tips](#tips-8)
  - [Glue](#glue)
    - [Glue vs. Data Pipeline](#glue-vs-data-pipeline)
    - [Glue vs. EMR](#glue-vs-emr)
    - [Glue vs. Database migration service](#glue-vs-database-migration-service)
    - [Glue vs. Batch](#glue-vs-batch)
    - [Glue vs. Kinesis Data Analytics](#glue-vs-kinesis-data-analytics)
  - [Chapter Summary](#chapter-summary)

## Service catalog

* Lists approved products and granted permissions to users via IAM.
* Resources are reached via personalized portal 
* Centralized control to meet standard, compliance, budget requirements, etc.
* Products of service or application; anything that can be defined via cloudformation.
    
The portfolio is a menu of items or groups of items that can be granted to users via IAM to browse and launch products they have access to.
    
* It is a regional based feature
    
```
Service Catalog under Mgt and Governance
├── Create Portfolio
├── Create product via cloudformation template
├── Add product to portfolio
├── Add a user, group or role
└── In IAM add existing policies
```
* IAM requires at least `serviceCatalogEndUserFullAccess` along with whatever is needed for the cf template, like s3 permissions.  
* IAM will also give a url for the portal
add access from the portfolio to the users, groups or roles as you want.
* You can also share this with other accounts or units in the organization.
    
To terminate, as the granted user you can go to your products and terminate the created resource ( runs the cf job to remove the resources)
    
### Tips:
  * Portfolio of products
  * Available as a portal
  * Runs CloudFormation templates
  * Control access via IAM
  * Helps enforce standards via standardized templates 
    
## Policy wildcards

`Arn:aws:s3:::examplebucket/*` is all items in the bucket
    
So a **policy statement** could be principal user, an **Action** == putobject and **Resource** == any file in a bucket
    
-Or-
    
User is allowed s3:* (any s3 action), and objects in the bucket
    
-Or-
    
User, gets a list of actions, specific item like deleting
    
Bucket-level actions
* S3:createbucket, deletebucket, etc

When referencing you must use the actual bucket name
    
Object-level actions 
* Resource users wildcard, all objects
        
### Tips:
* Wildcard is all actions, `s3:*`
* All objects in a bucket. `Examplebucket/*`
* Bucket level actions use the bucket name without wildcard
        
## CloudFront errors

HTTP status code.
Served from ec3 and references a bucket, accessed via CloudFront
    
Some problem happens, CloudFront returns an error code, either 4xx of 5xx
* 4xx is a client side error; bad request, 403 - access denied, 404- file not found, etc.
* 5xx is server side; 52 bad gateway, 503 - Service unavailable, 504 - Gateway timeout; often caused by high traffic to the website and the server is not responding
    
### Tips: 
* 400 is always client side
  * Check that the object exists
  * You have access
  * The request is correctly formed
* 500 are always server side

## Multi-Account Access To Direct Connect

* Provides secure reliable fast and consistent connection from your data center to you assorted VPC's
* Allows multi-account access using the same payer account to up to 10 VPCs
* The VPCs don't require being in the same account so long as they are all in the same organization

### Tips

* Multiple accounts to separate workloads is best practice (dev, test, prod, etc)
* Organizations to manage the accounts under the same payer
* Direct connect doesn't need a distinct gateway for each account.
* Accounts under the same payer can share the direct connect gateway.

## Inter-Region VPC Peering

Allows 2 VPC's to connect to each
other, even cross accounts

* Older method was to setup a VPN between the VPCs but now you can link the two VPCs in different regions together.  
* Update the route tables between the two after linking them and you are done
* Connections are on the internal AWS network

### Tips

* You can do it; allowing 2 VPCs in different regions to communicate using the AWS global network
* Traffic is encrypted
* Never hits the public internet
* CIDR ranges must be unique with no overlap
* May not be available in all regions

## HTTPS & Storing SSL Certificates

* Common to connect via SSL using trusted certificates to encrypt in transit via TLS encryption.
* Uses SSL/TLS certificate
* AWS certificate manager can provision, manage and deploy your certificates
* Can use new or existing certs
* Certs provided by ACM are free and renew automatically.
* Using IAM to store certs?  
  * Possible but only for enabling HTTPS connections in a region not supported by ACM.
  
### Tips

* When enabling HTTPS on your website, you need to associate an SSL/TLS certificate
* Recommended way is t o store and manage certificates is with the ACM
* Only use IAM to store certs if ACM isn't supported in your region.

## CloudFormation Best Practices

* Very powerful and can be risky since it can deploy resources at cost.
* Use IAM to control access to CF
* Be aware of service limits on creating resources
* Avoid manual updates since they create mis-match between your template and the current state of the stack causing errors on update / delete
* Use cloudtrail to audit changes
* Set a stack policy for critical resources
  * Describes what update actions can be performed on designated resources.
* Helps to protect against human error
```json
{
  "Statement" : [
    { 
      "Effect": "Allow",
      "Action": "Update:*",
      "Principal": "*",
      "Resource": "*"
    },
    {
      "Effect": "Deny",
      "Action": "Update:*",
      "Principal": "*",
      "Resource": "LogicalResourceID/ProductionDatabase"      
    }
  ]
}
```

### Tips

* Use IAM to control access to CF
* Manage service limits to avoid deploy failure
* Avoid manual updates because of state mis-matching
* Use CloudTrail to audit changes
* Use Stack policy for critical resources

## CloudFormation Failed Rollback

* On failure by default all resources in the stack get rolled back to the previous state, including deleting the stack.
* It might fail because of something being changed outside of cloudformation
* If the rollback fails because of manual change you have to fix by hand.
* Ex.
  * Resource no longer exists: rollback to an old database instance that was removed outside of CF.
  * Manual recreate the resources as CF expects before trying the rollback again.

### Tips

* Update_rollback_failed: CF can't rollback
* Stacks in this state cant be updated further
* To resolve you have to fix the error causing the failure, either by creating the missing resource or using the CLI to expressly keep some items that are already deleted so you can finish the rollback.

## Additional Resources To Help You Prepare For The Exam

* Find common answers in the FAQS
* Whitepapers have lots of detail on guidance and best practices
* re:Invent videos
* FAQs
  * Cloudwatch FAQ
  * Cloudformation and elasticbeanstalk
  * S3 RDS, Athena Elasticache
  * IAM, KMS, Inspector, Trusted advisor
  * VPC, Route 53, direct connect ELB, EC2
  * Cloudformation, Systems Manager, Config
* Whitepapers
  * Development and test on aws
  * backup and recovery approaches
  * VPC connectivity options
  * Security best practices
  * Security processes
  * Well-architected framework
  * Architecting for the cloud
  * web application hosting in the AWS cloud
  * Building scalable and secure multi-vpc network
  
### Tips

* Browse the entire document (skim it)
* Revisit the sections that seem worth reading
* Keep in mind what you want to get out of it
* Take notes
* re:invent videos of most of the whitepapers

## Glue

A fully managed on demand ELT service to automate the steps of data prep for analytics.

Data is auto processed via glue catalog which recommends and generates the ETL to transform the source data into target schema and can run that job on fully managed Apache Spark to load the data to the target.  It also allows setup, orchestration and monitoring of complex data flows

Main components:
  * Data catalog - Central metadata repo
  * ETL engine - Generate scala or python that can be customized further
  * Scheduler - Dependency resolution, job monitoring and retries

Used for discovery of properties of your data, transformation of the data and prep for analytics.  It can handle structured and semi-structured data from:
  * S3 data lake
  * Redshift data warehouse
  * Assorted databases running on aws

Results querying is done via Athena, ERM or Redshift spectrum.

Supports data natively from: 
  * Aurora
  * RDS (MySQL, Oracle, PostgreSQL, SQL Server)
  * Redshift
  * S3
  * On instance installs of the RDS engines

Metadata in the glue data catalog can be read via Athena, EMR, or redshift or via custom Scala / python code.

Data lake is related to glue via shared infrastructure, including console controls, ETL generation and job monitoring.  Additionally there is a common data catalog and both use serverless architecture.  Lake formation is all of glue AND additional features to build, secure, and manage a data lake.

The data catalog is the central repository of structural and operational metadata of all data assets. This allows you to store table definition, location, business relevant attributes and track how the data has changed over time.

The catalog is Apache Hive Metastore compatible and can be a drop-in replacement for applications running on EMR.

You can get metadata via the provided crawler scanning datastores to automatically infer schemas and partition structures. You can also schedule crawlers to run onn a schedule to keep metadata up to date with the data. 

You can also add / update table details using the console or via API calls.

Lastly if you have a Hive Metastore you can do a bulk import of that metadata into the data catalog via an import script.

The crawler connects to the data store and processes through a prioritized list of classifiers to extract the schema of your data and other statistics to populate the data catalog with. The crawler will automatically add new tables, partitions to existing tables, and new versions of table definitions.

FindMatches feature solves record linkage and de-duplication problems.
Record linkage is basically the same problem as de-duplication but is based on 'fuzzy joins' rather than knowing something is a duplicate based on record number. This feature uses machine learning algorithms to learn how to match records according to the developers business criteria.

First by identifying records for the customer to label if it is a match then using machine learning to create an ML transform.  That transform could then be used on the database to find matching records or ask for more sample records to manually process to give the ML additional training.

The data catalog can be encrypted at rest, and SSL for data in motion.

Glue pushes notification to CloudWatch and you can setup SNS notifications of those items to be informed of job failures or completions.

Glue provides an SLA of 99.9% uptime on a monthly basis.

### Glue vs. Data Pipeline

Glue is a serverless ETL service run in Apache Spark so you don't need to worry about configuring underlying resources and is thus a data first service. Glue is based in either Scala or python.

Pipeline is a managed orchestration service that gives greater flexibility in terms of execution environment, access and control over the compute resources and the code that does the data processing.  

If your processes requires something other than Scala || python or an engine other than Spark then use Data Pipeline. Otherwise Glue may be a good choice.

### Glue vs. EMR

Glue provides automatic scale-out for ETL jobs.  By inference it will evolve and monitor ETL jobs to simplify the process of creating and maintaining jobs.

EMR provides direct access to a hadoop environment, giving access to tools beyond Spark.

### Glue vs. Database migration service

DMS is for migrating databases into AWS.  Once data is in AWS you can use Glue to move and transform data from that source to another database or data warehouse.

### Glue vs. Batch

Batch is for running any batch computing job regardless of the nature of the job.  It does this be creating and managing compute resources in the account giving full control and visibility into the resources being used.

Glue is fully-managed serverless environments for ETL jobs.  

In most ETL cases glue is the likely better fit, but some batch cases including specific ETL use cases, batch may be a better fit.

### Glue vs. Kinesis Data Analytics

Kinesis allows running standard SQL queries on incoming data streams with the results written out to a destination location like S3.  Once data is available in a target source then ETL can be run for further transformation to prepare it for additional analytics and reporting.

## Chapter Summary

* Service catalog
  * A portfolio of products (cf templates) presented as a portal
  * Access control via users, groups, and roles get access to a portfolio
  * Enforces standards by only allowing approved resources that are in compliance with internal policies, services, configuration, and tagging.
* Wildcards in S3
  * Can be used for actions, objects
  * For bucket level actions use the bucket name
* Cloudfront errors
  * 4xx (client side: access, request format, access, etc) vs 5xx (server side; origin not responding because of server down / unavailable)
* Direct connect supports multi account access to your data center using organizations with a limit of up to 10 VPCs
  * Best to separate workloads based on workload (dev, etc)
  * Arrange with organizations to manage under one payer
  * You don't need multiple gateways in this configuration
  * Accounts under the same payer account can share a direct connect configuration
* VPC peering - inter-region is possible
  * Goes through the global network never the internet
  * Traffic is encrypted
  * CIDRs need to be unique
  * Not in all regions yet
* HTTPS
  * Needs a certificate
  * Suggested to manage using ACM (AWS certificate manager)
  * IAM can do it but only when ACM isn't supported in that region.
* CF Best practices
  * Use IAM to control access
  * Manage service limits to avoid failure
  * Avoid manual updates to avoid failure on update / delete
  * Use CloudTrail for auditing API calls
  * Use stack policy on critical resources to protect human errors
* CF Rollback failed
  * Prevents stack update when in rollback failed
  * Have to fix the error by hand because the stack changed by hand
  