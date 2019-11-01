## Chef

Pros: 
* established
* common?

Cons:
* lots of dependencies
* if dependencies are not pinned you can end up painted into a corner where you are stuck with multiple conflicts that become hard to resolve

Needs:

Chefdk
virtual box
git
vagrant

Extra steps for prep were needed since you can't have hyperv and virtualbox working on the same machine at the same time.

Reboot and hold shift to access boot menu to select the non-Hyper-V env
Default boot has Hyper-V enabled
Prep the box: 
`vagrant box add generic/centos7 --provider=docker`
`vagrant init generic/centos7`
`vagrant up` 


