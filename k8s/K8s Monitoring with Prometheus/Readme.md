## Logging

data about the state or an event of an app / service
often log form providing detail about the state change

## metering

data about the rate of change
time series based

log info `/var/log/syslog`

could be used for metrics / metering but isn't metering by default

`top` is more metering since it is point in time metric that could be gathered and displayed as resources consumed over time

## tools

cAdvisor - container monitoring exposing individual container metrics. It is focused on single containers which makes it less common
Heapster - Tool that uses cAdvisor to collect data from kubelet for central storage
Prometheus - Generic pull based time-series system with k8s integration

