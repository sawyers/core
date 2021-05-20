# Automation

- [Automation](#automation)
  - [CloudFormation](#cloudformation)
    - [Tips](#tips)
  - [Cloudformation Lab](#cloudformation-lab)
  - [ElasticBeanstalk](#elasticbeanstalk)
    - [Tips](#tips-1)
  - [ElasticBeanstalk Lab](#elasticbeanstalk-lab)
  - [OpsWorks](#opsworks)
    - [Tips](#tips-2)
  - [Summary](#summary)
  - [Quiz](#quiz)
    - [Key](#key)

## CloudFormation

* A service to manage configure and provision infrastructure as code via a template.
* The template is interpreted and makes the correct API calls based on the definition
* Supports YAML or JSON

Benefits:
* Provisioned consistently with fewer mistakes
* Faster and easier than manual configuration
* Version control and review templates
* Free service
* Mange updates and dependencies
* Manage rollback or delete of the entire stack

Template in YAML or JSON to describe the endstate and after creating you upload it to S3.

CF reads the template to make API calls for you

The product is a stack.

The template is a series of key value, lists, etc.

Templates can be nested to keep stacks from being too large to handle

Only the `Resources` section is required but most would have parameters, mappings etc.

Transform section is used to reference additional code from S3 for code re-use, lambda code or template snippets.

### Tips

* Manage infrastructure as code (YAML/JSON)
* Main sections:
  * Parameters - user input
  * Conditions - Provision based on environment
  * Resources - Required and is what resources are created
  * Mappings - Create custom mappings like Region : AMI
  * Transforms - reference code located in S3 eg. Lambda code or reusable snippets.

## Cloudformation Lab

```yaml
AWSTemplateFormatVersion: 2010-09-09

Description: Template to create an EC2 instance and enable SSH

Parameters: 
  KeyName:
    Description: Name of SSH KeyPair
    Type: 'AWS::EC2::KeyPair::KeyName'
    ConstraintDescription: Provide the name of an existing SSH key pair

Resources:
  MyEC2Instance:
    Type: 'AWS::EC2::Instance'
    Properties:
      InstanceType: t2.micro
      ImageId: ami-0de53d8956e8dcf80
      KeyName: !Ref KeyName
      SecurityGroups:
        - !Ref InstanceSecurityGroup
      Tags:
        - Key: Name
          Value: My CF Instance
  InstanceSecurityGroup:
    Type: 'AWS::EC2::SecurityGroup'
    Properties:
      GroupName: MyDMZSecurityGroup
      GroupDescription: Enable SSH access via port 22
      SecurityGroupIngress:
        IpProtocol: tcp
        FromPort: 22
        ToPort: 22
        CidrIp: 0.0.0.0/0

Outputs: 
  InstanceID:
    Description: The Instance ID
    Value: !Ref MyEC2Instance
```

Upload to S3 or upload as part of deploying the CF.

This example uses a hard coded value for AMI that only exists in the EU. To find an AMI in your region, go through the console to the region you want and search for and copy the AMI number of the AMI you want to use.  Or you can use custom mapping for each region.  

Setting global SSH isn't best practice, but CF doesn't by default have a way of letting the S3 template discover the IP of the station you are running from.

Default behavior is rollback on failure, but sometimes you are deploying code along with the infrastructure so you would set it to not rollback so you could have an option to look into the instance.

## ElasticBeanstalk

* Service to deploy and scale web applications in many common languages like Java, .NET, PHP, Node.js, Python, Ruby, Go, Docker on platforms like Tomcat, Nginx, Passenger, Puma, and IIS.
* Upload the code and beanstalk does the rest. 
* You only pay for the resources required to deploy
* The fastest and simplest way to deploy
* Auto scales up and down
* You select the instance type
* You can have full admin control over the resources are allow it to be automatic
* Managed platform updates to OS and languages
* Monitor and manage the app via dashboard
* Integrated with cloudwatch and x-ray for performance data and metrics
  
### Tips

* Deploy and scale web applications including the web server platform where required
* Supports widely used programming technology:
  * Java
  * .NET
  * PHP
  * Node.js
  * Python
  * Ruby
  * Go
  * Docker
* Includes common server platforms:
  * Tomcat
  * Nginx
  * Passenger
  * Puma
  * IIS
* Provisions the supporting resources
* Can manage instance for you or let you do it
* Manages updates, monitoring, metrics and health checks

## ElasticBeanstalk Lab

Launch a beanstalk using a basic web app uploaded as a zip file, selecting the platform you are running under.

Then create the application.

There are some other options you can set as you like, including scale up / down rules, tags, etc.

The creation doesn't provide a 'friendly' DNS name, but you should be able to alias that if you need to.

Configuration overview gives summary of the setup, monitoring via cloudwatch data, application events, etc.

If you only need a platform to run the code then beanstalk is simple to get going, but if you need other resources created together then cloudformation may be the better choice.

## OpsWorks

* Automate via Puppet or Chef
* Provides managed instances for the controller
* Automate server config using code
* Works with existing code
* Automate complex tasks, NTP configuration, etc.

### Tips

* it's automation via chef or puppet with a managed controller.
* If you have a requirement to manage EC2 using one of these tools then it is the quickest path.

## Summary

* CF allows managing, configuration and provision of infrastructure as code with YAML or json
* Main sections
  * Parameters - User input
  * Mappings - Custom mappings of condition / value
  * Resources - Created resources
  * Conditions - Based on environment
  * Transform - include resources from S3 like lambda code or snippets
* On deploy failure default is to rollback the stack
* You can disable that setting if needed for troubleshooting
* Elastic Beanstalk deploys and scales web applications including the server platform where required 
* Supports common programming technologies and platforms
* Provisions underlying resources for you
* Will admin the instances for you or let you do it
* Includes monitoring metrics and health checks

## Quiz
1. You would like to deploy a web application which is going to run on Tomcat, which of the following services would allow to quickly deploy the application without having to worry about configuring and managing the underlying infrastructure?
- [ ] Cloud Formation
- [ ] EC2
- [ ] Elastic Beanstalk
- [ ] Lambda
2. Which of the following are not valid CloudFormation template sections?
- [ ] Parameters
- [ ] Resources
- [ ] Options
- [ ] Outputs
3. Which section of the CloudFormation template allows you to set a custom key with a corresponding set of values?
- [ ] Resources
- [ ] Conditions
- [ ] Mappings
- [ ] Transforms
4. What data formats are used to create CloudFormation templates? (Choose 2)
- [ ] JSON
- [ ] CSV
- [ ] YAML
- [ ] XML
5. How can you prevent CloudFormation from deleting your entire stack on failure? (Choose 2)
- [ ] Set Termination Protection to Enabled in the CloudFormation console
- [ ] Use the --disable-rollback flag with the AWS CLI
- [ ] Set the Rollback on failure radio button to No in the CloudFormation console
- [ ] Use the --enable-termination-protection flag with the AWS CLI
6. You have some code located in an S3 bucket that you want to reference in your CloudFormation template. Which section of the template can you use to define this?
- [ ] Inputs
- [ ] Transforms
- [ ] Resources
- [ ] Files
7. Which of the following sections of the CloudFormation template would you use if you wanted to create a specific set of resources based on the value of a parameter?
- [ ] Transforms
- [ ] Outputs
- [ ] Resources
- [ ] Conditions
8. You are deploying a number of EC2 and RDS instances using CloudFormation. Which section of the CloudFormation template would you use to define these?
- [ ] Instances
- [ ] Outputs
- [ ] Resources
- [ ] Transforms
9. You have designed a CloudFormation script to automatically deploy a database server running on EC2 with an attached database volume. This CloudFormation script will run automatically when a predefined event takes place. The database volume must have provisioned IOPS, and cannot have any kind of performance degradation after being deployed. What should you do to achieve this?
- [ ] Test the CloudFormation script several times, and load-test it to a value matching the anticipated maximum peak load.
- [ ] Design the CloudFormation script to use MongoDB. MongoDB is designed for performance, and is much better than any other database engine out there.
- [ ] You should not be using CloudFormation. Instead, it would be better to script this using CodeDeploy.
- [ ] Design the CloudFormation script to attach the database volume using S3, rather than EBS.
- [ ] Using a combination of CloudFormation and Python scripting, pre-warm the EBS volumes after the EBS volume has been deployed.
10. In a CloudFormation template, which of the following is used to define input values?
- [ ] Parameters
- [ ] Transforms
- [ ] Resources
- [ ] Conditions 
11. Which of the following sections of the CloudFormation template would you use if you wanted to create a specific set of resources based on the value of a parameter?
- [ ] Transforms
- [ ] Outputs
- [ ] Resources
- [ ] Conditions
12. You are using CloudFormation to create a new S3 bucket, which of the following sections would you use to define the properties of your bucket?
- [ ] Parameters
- [ ] Resources
- [ ] Outputs
- [ ] Conditions
13. Your company has moved to AWS so it can use "Infrastructure as Code". You would like to apply version control to your infrastructure, so that you can roll back infrastructure to a previous stable version if needed. You would also like to quickly deploy testing and staging environments in multiple regions. What services should you use to achieve this?
- [ ] DynamoDB and CloudFront.
- [ ] CloudFormation and CodeCommit.
- [ ] Elastic Beanstalk and CodeCommit.
- [ ] EC2 and RDS.
- [ ] CloudWatch and CodeCommit.
- [ ] OpsWorks and CodeCommit.
14. Which section of the CloudFormation template is mandatory?
- [ ] Resources
- [ ] Conditions
- [ ] Transforms
- [ ] Parameters
15. You want to use the output of your CloudFormation stack as input to another CloudFormation stack. Which section of the CloudFormation template would you use to help you configure this?
- [ ] Resources
- [ ] Transforms
- [ ] Exports
- [ ] Outputs
16. Which service allows you to manage, configure and provision your AWS infrastructure as code?
- [ ] CloudFormation
- [ ] Elastic Beanstalk
- [ ] Config
- [ ] Systems Manager
17. In a CloudFormation template, which of the following is used to include code you have stored in S3?
- [ ] Parameters
- [ ] Conditions
- [ ] Transforms
- [ ] Resources
18. Which two things can you define using the Transforms section of the CloudFormation template? (Choose 2)
- [ ] To re-use code located in S3
- [ ] To transform API responses to a supported format
- [ ] To convert between YAML and JSON format templates
- [ ] To specify the use of the Serverless Application Model for Lambda deployments
19. Part of your CloudFormation deployment fails due to a misconfiguration, by default what will happen?
- [ ] Failed components will remain available for debugging purposes
- [ ] CloudFormation will rollback only the failed components
- [ ] CloudFormation will ask you if you want to continue with the deployment
- [ ] CloudFormation will rollback the entire stack
20. Which AWS service can you use to deploy and scale web applications in the cloud without configuring your own infrastructure?
- [ ] Elastic Beanstalk
- [ ] EC2
- [ ] Lambda
- [ ] Cloud Formation

### Key
1. Elastic Beanstalk
2. Options
3. Mappings
4. JSON & YAML
5. `Use the --disable-rollback flag with the AWS CLI` & `Set the Rollback on failure radio button to No in the CloudFormation console`
6. Transforms
7. Conditions
8. Resources
9. Test the CloudFormation script several times, and load-test it to a value matching the anticipated maximum peak load.
10. Parameters
11. Conditions
12. Resources
13. CloudFormation and CodeCommit.
14. Resources
15. Outputs
16. CloudFormation
17. Transforms
18. `To re-use code located in S3` & `To specify the use of the Serverless Application Model for Lambda deployments`
19. CloudFormation will rollback the entire stack
20. Elastic Beanstalk