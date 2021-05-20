# Cloud native computing foundation

Vendor neutral home and part of the linux foundation.  A firewall between users
and the corp that created the tool and looks for new projects that might fit in.

They keep projects and platforms listed on their home page

Ones with white background are open source, gray isn't, and is split across
assorted sections.

They are also a cert issue for technology.

## Management and orchestration

building and deploying, GRPC is a replacement for things like rest and serializes
interactions and contracts.

Deploy containers with k8s as a general rule

Service discovery is easier with k8s since the definition allows a back end to
manage the network layer internal to the services. Suggests CoreDNS if you need
a DNS, or kube-dns for service discovery.

Kube-dns is built in making it pretty default but likely will end up being coreDNS
in the future as the default

Managing cloud native services. As the platform grew there were more and more asks
against the tools to manage and deploy.

See service mgt to see service mesh

The layer that handles all comms and network between services linkerd is a transparent
network proxy that manages internal connections and is aware of most of the expected
features

Then envoy is another option, small server with small footprint supporting grpc along
with the other expected features and API's.

The differences is that linkerd is a bit heavier along with having thrift which envoy doesn't.

Either should work, but some feature specific requests may suggest one over the other.

## networking and runtime

Container networking can be confusing.  had been no standard to integrate networks
till Container a generic plugin based solution, that says it must create the runtime for
the containers determine which networks the container should be log to, install plugins etc.

suggestions, see what is most popular at the time that fits your use case, flannel or
project callico are currently popular

Container storage, is pretty important, with rook being a big project currently

it brings storage into k9s and orchestrates ceph on top of k9s it is also integrated
with k8s for seamless use

runtimes are containerd currently and manages container lifecycle of the host system

## Observability analysis and security

Most major projects support cncf but prometheus is the biggest it simplifies monitoring
the cluster and can scrape the API you can also scrape the app inside k9s it has a good
query language to build rules it includes alert manager and integrates with other tools
connects well with grafana for dashboards Some places already have a monitoring tool,
and most can also monitor if you already have purchased something.

logging with fluentd, but elasticsearch or splunk are also big projects.

Fluentd is aa log aggregator that works just like ELK it is very popular with strong community

it is slightly lower weight than elk, but both will work.

Debugging with tracing tools. jaeger and opentracing are big. Instrument the app with
required API's etc.

Security is proactive for security of images and keys

lots of PPI get passed via docker and can be managed in tools like vault.  Notary or
blackduck are examples of image security.
