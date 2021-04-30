# SRE role in III devops

What roles and tasks could a SRE cover in iii devops?

## What does a 'generic' SRE do?

Wikipedia says it is a dicipline that aplies devops tools and pratices to infrastructure and operations problems to create scalable and reliable systems.

SRE's apparently spend ~50% of their time doing ops work interrupts (issues, support, manual intervention) and the other time spent on development tasks related to new features and automation / scaling.

* Sets service level indicators and objectives and post mortems
* Reduce the risk of failure to help development move quicker
* Automate menial tasks 

Another source defines it as:

> The team responsible for availability, latency, performance, efficiency, change management, monitoring, emergency response and capacity planning.

Google simply says the goal of an SRE is to "automate their way out of a job" by building self service tools for users that rely on other services (auto provisioning env, logs, stats visulations)

## How does that mesh with what we do at iii?

* The most commen requests against devops are already automated via opsbot.
* No disaster recovery process / testing. If nexus goes down, how long to get it running again? if jenkins master gets deleted, how long to recover and do we have backups to restore to some reasonable point in time?
* Patching / major updates to infrastructure products.


## Possible duties of an III devops SRE

Identify more areas of self service automation. We have opsbot that does many self service actions, but have not been adding to it in some time. Are there areas that could be expanded on?
* Attach encore to arbitrary stack (longer process time to sync data, but otherwise may not be that complex)
* Automated backup and restore (not snapshot) of ILS to allow 'profiles' of pet machines... Tricky in that the backup doesn't check for data conversion so could only be used on the same application version.
* Automated security tests against products? Pen tests in aws are not as restrictive as they once were, maybe we should look at starting that process? https://aws.amazon.com/security/penetration-testing/
* Add visibility to devops team work; both in unified automated reports but in having transparency to tickets resolved automatically. tasks automated away to fully auto or even self service should still generate tickets to record the work and that work should be published ( 500 tickets resolved automatically this quarter ).

