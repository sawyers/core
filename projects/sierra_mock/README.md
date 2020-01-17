# Docker Sierra Combo

Record resources to create a Sierra 5.0 combo server as a docker file, minus data.

It is intended to be used for quick prototyping or Ansible role testing without needing
a full Jenkins build cycle.

It is not intended to replace Jenkins, only to help speed up development with Jenkins being
a final test.

## Status

This project was unsuccessful. Using minimal layers, using squash, removing files when possible in the same layer, nothing helped keep the container size under control.

Sierra itself, just for the software dir, is 15gb.  Facing that challenge I was unable to create even a minimal Sierra container for under 16gb. It just isn't happening no matter what I try.  As Sierra is a monolith product not designed to be split up, there is no point in continuing the work in this way since it will never result in a container that I could consider usable. 


## Who owns it

This repo is managed by DevOps

## System Requirements

* docker

## How do I use it

Dockerfile will build an image with Sierra installed.
The user must provide Sierra_50/secrets file with aws key and secret.
This file is in .gitignore to prevent going into source control. The access
granted is to the rls-eng owned AWS S3 bucket and is published in the [internal
wiki](http://insight.iii.com/InstallConfigGuide/NewsiteSierra2_0Rawinst#STEP_3_SFTP_FTP_SOFTWARE_IMAGE)

Example usage:
  docker build -t molecule-iii/sierra .
  `save and tag image`
  `upload fat image to nexus`

## How do I test it

There are no tests at the moment.

### Data

* rawinst_response prompt and answer mapping
  * **Please enter your III login name :** dkr
  * **ENTER NODE NAME :** devops-dkr
  * **Is this an Application server?** ? y
  * **Is this the server where the postgres database will be installed?** y
  * **Will lucene be configured on this server? ?** y
  * **Will the dataservice run on this server? ?** y
  * **Is this the server where backups will be run? ? (y/n)** y
  * **Should the root (not iiiroot) password be automatically reset on a monthly basis ?** y
  * **AVAILABLE DATE DISPLAY FORMAT :** 1
  * **ENTER SITE NAME :** devops-dkr
  * **Do you want to alter the Language status ?** n
  * **Does this site use Hangul Indexing for Korean word splitting? ?** n
  * **Does this site use custom increased number of approvals files? ?** n

### Comments

This is a massive docker image because it involves installing ~2gb worth of OS packages. While it is very
likely that we have no need for many of them in fact, they are all listed as required in the documentation.
For this image to be used to test processes that involve something like bldsys it needs to be 'complete' as
far as the product is concerned. Attempting to cut down the final size, eg. coping the compiled Sierra app
to a new clean container with a smaller subset of package may make the size better but the overall use may
break when commands can't find the expected OS resource.
