# Linkedin Learning

## Chap 1 - Installing docker

- Over all rather basic info.
- Run bash as interactive shell under Ubuntu and remove the image after exit
: `docker run -ti --rm ubuntu bash`

---

## Chap 2 - Using docker

- Docker flow
: image -> `docker run` -> Running container
  - Images are fixed good points to allow consistent behavior
  - On exit changes are saved off
- Stopped containers can then be saved as new images to save setup.
- `docker commit <container name> <tag name>`

### Run cmd to get output then remove the container after

- `docker run --rm -ti centos yum info ansible`
- Detached containers (start and let it keep going in the background as a service)
: `docker run -d -ti ubuntu bash`
- A bit silly to run bash in the background since it doesn't do anything but it is an example.
- Connect to running container, and leave it running when you exit
: `docker attach <container name>`
- Add processes to running containers (excluding ports/volumes/...)
: run additional exec to shell or run commands
- Logs of containers, even halted ones
: `docker logs <container name>`
- Saved logs / lots of logs can slow down docker
- Cleanup
: stop containers then rm them
- Limit containers
: `--memory <max mem>`, `--cpu-shares <vs other containers>`, `--cpu-quota <limit in general>`
- Orchestration often requires limits
- Suggestions
  - Don't fetch dependencies on start, make the containers with all dependencies
  - Don't leave anything important in unnamed stopped containers

### Networking between containers

- Containers are isolated by default from the internet
- Containers are _linked_ by _exposed_ ports
- What is typed in shell 2 is echoed in shell 3 because of docker
  - `[Shell 1] docker run --rm -ti -d -p 45678:45678 -p 45679:45679 --name echo-svr ubuntu:14.04 bash -c 'nc -lp 45678 | nc -lp 45679'`\
    `[Shell 2] nc localhost 45678`\
    `[Shell 3] nc localhost 45679`
- The same thing can be done from container to container using the hosts IP
  - `[Shell 1] docker run --rm -ti -d -p 45678:45678 -p 45679:45679 --name echo-svr ubuntu:14.04 bash -c 'nc -lp 45678 | nc -lp 45679'`\
    `[Shell 2] docker run --rm -ti ubuntu:14.04 bash`\
    `[Shell 2] nc <Host IP> 45678`\
    `[Shell 3] docker run --rm -ti ubuntu:14.04 bash`\
    `[Shell 3] nc <Host IP> 45679`
- Exposing ports has to be done up front, or expose ports dynamically where the port in the container is fixed, but from outside you get next available port
  - `docker run --rm -ti -d -p 45678 -p 45679 --name echo-svr ubuntu:14.04 bash -c 'nc -lp 45678 | nc -lp 45679'` \
    `docker port echo-svr`\
    `45678/tcp -> 0.0.0.0:32769`\
    `45679/tcp -> 0.0.0.0:32768`
- Often done with service discovery external tools
  - Default ports are tcp, but you can say udp
  - Ports are "**inside out**", input first followed by output
  - Containers can converse through the host
    - `[Shell 1] docker run --rm -ti -p 1234:1234 ubuntu:14.04 bash`\
      `[Shell 1] nc -lp 1234`\
      `[Shell 2] docker run --rm -ti ubuntu:14.04 bash`\
      `[Shell 2] nc <Host IP> 1234`\
      `[Shell 2] hello`\
      `[Shell 1] hello`

### Docker linking and manged virtual network

- More efficient is to link containers via virtual network within docker, linking all ports from one to another.
- Linking is done one way from the machine started to the linked machine
- Only for services intended to be on the same machine, service + health check for example
  - `[Shell 1] docker run -ti --rm --name svr ubuntu:14.04 bash` \
    `[Shell 1] nc -lp 1234` \
    `[Shell 2] docker run -it -rm --link svr --name client ubuntu:14.04 bash`\
    `[Shell 2] nc svr 1234`
- Prevent links from breaking on container restart via private network
  - Network must be made in advance
    - `[Shell 1] docker network create example`\
      `[Shell 1] docker run --rm -ti --net=example --name server ubuntu:14.04 bash`\
      `[Shell 1] nc -lp 1234` \
      `[Shell 2] docker run -it -rm --link svr --net=example --name client ubuntu:14.04 bash`\
      `[Shell 2] nc server 1234`
- Use to use env vars inside the container but it still works for now
- When a service moves to a container local services by default are only listening to that container
- To allow connections you bind address 0.0.0.0 inside the container
  - `docker run -p 127.0.0.1:1234:1234/tcp`

### Docker images

- Normally tagging with org / version is enough
- Images can build up quickly without attention, you can clean images with
  - `docker rmi <image-id>`

### Volumes

- Allow shared storage between containers, the host, or to serve as persistent storage
- You can also share folders and files in the same way ports are done, inside / outside
  - `docker run -ti -v /users/example:/shared-folder ubuntu bash`
- Ephemeral volumes shared between containers
  - `docker run -ti -v /shared-data ubuntu bash` \
    `docker run -ti --volumes-from <Source> ubuntu bash`
- So long as at least 1 container with shared volumes exists the shared volume exists and can be shared with others.  Once all containers exit the volume is gone

### Registries

- We use nexus at iii, which is common for corporations, or you can use the docker created or other private ones. Search the repo with CLI or web GUI
  - `docker search <keyword>`
- Don't push images with passwords or other authentication in the container
- Clean up images regularly to avoid old dependencies
- Be careful on trusting downloaded containers.

---

### Dockerfiles

- Data used to describe how docker build creates an image
- Each step makes a new image, consider the order of actions and grouping commands to avoid large images (eg. download / process / cleanup in one action to only have one image level)
- Parts that change the most belong at the end of the dockerfile
- These look like shell scripts but they are not shell scripts
- ENV will set vars that persist from action to action
  - Example \
    `FROM debian:sid` \
    `RUN apt-get -y update` \
    `RUN apt-get install nano` \
    `CMD ["bin/nano", "/tmp/notes"]`
- Then build an image from that example.
  - `docker build -t deb .` \
    `docker run --rm deb`
- You can also use the from pointing to other tags to build from other containers
  - FROM
  : what image to start from and should be at the start, but you can have more than one FROM
  - MAINTAINER
  : Who manages the container and how to contact
  - RUN
  : do a shell command(s) against that container
  - ADD
  : add file or extract tar.gz or other compressed archive or download from URL to target location
  - ENV
  : Set for duration of docker file and in final image
  - ENTRYPOINT / CMD
  : Beginning expression to use when starting container and allows arguments passed by `docker run`. If you have both they get strung together, but entrypoint lets docker look more like a normal program.  Both take shell form `nano notes.txt` or exec ["/bin/nano, "notes.txt"]
  - EXPOSE
  : define ports as before
  - VOLUME
  : create mapping of shared volumes or ones shared for other containers
  - WORKDIR
  : Sets dir the container starts in
  - USER
  : Run commands as named user or user ID
- Multi-stage builds (new feature)
  - `FROM ubuntu as builder` \
    `run apt-get update` \
    `run apt-get -y install curl` \
    `RUN curl https://google.com | wc -c > google-size`\
    `FROM alpine`\
    `COPY --from=builder /google-size /google-size`\
    `ENTRYPOINT echo google is this big; cat google-size`
- Avoid golden images
  - Include the installer in your project
  - Have a canonical build that builds everything from scratch
  - Tag your builds with the git hash of the code that built it
  - Use small base images like Alpine when possible
  - Build images you share from Dockerfiles every time
  - Don't leave passwords / tokens in the layers

### Docker and Kernels

- Runs on the hardware and manages software / hardware connections
  - Runs programs
  - Manages storage
  - Passes messages between programs
  - Docker manages the kernel using
    - Control groups to contain processes inside the kernel
    - Namespaces to split the network stack
    - Copy-on-write file systems for images
  - Docker is client / server model, but the client can be inside the container

- docker networks
  - `docker run -ti --rm -v /var/run/docker.dock:/var/run/docker.sock docker sh`
  - you can start a container from inside a container, where the first container becomes the server and the nested container is the client.
  - Bottom layer, Ethernet layer, moves frames over network
  - Next IP layer, moves packets on local network
  - Routing: packets between networks
  - Docker uses bridges to create local virtual network in your computer with software switches at the ethernet layer.
    - `docker run -ti --net=host ubuntu bash` \
      `apt-get update && apt-get install bridge-utils` \
      `brtcl show`
  - Creating virtual networks creates that bridge(s) via `docker network create`
  - Routing uses built in firewalls via iptables, AKA NAT
  - Docker port forwarding example == exposing ports via -p flag
    - `docker run -ti --rm --net=host --privileged=true ubuntu bash` \
      `apt-get update && apt-get install -y iptables` \
      `iptables -n -L -t nat` \
      `docker run -ti --rm -p 8080:8080 ubuntu bash` \
      `iptables -n -L -t nat` shows new port forward rule
- docker processes
  - Each process is a parent / child starting with init, each process is a child of another
  - Name of root process
    - `docker inspect --format '{{.State.Pid}}' <container>`
  - Resource limiting (memory / CPU) is inherited (init)
- Unix storage
  - Lowest level, actual hardware
  - Logical storage based on hardware
  - File systems - map logical storage to data
  - FUSE file systems (programs that act like file systems) (COW - copy on write)
    - Instead of overwriting content copy the source then modify the copy as a layer to allow multiple variations based on the same starting image.
  - Moving COWS, different methods depending on what is available. Docker knows how to move from one form to another for you.
  - Containers are independent of the storage engin and can be loaded almost anywhere
  - It is possible to run out of layers depending on the storage engine but is rare
  - Volumes / bind mounting
    - Part of Linux VFS to mount devices or directories via the `mount -o bind` command
    - Mounting volumes is always from the host over the guest, not the the other direction

---

### Chap 5 Orchestration

- Docker registries
  - Storages images, layers, etc  - Manages authentication
  - Common options would be official Python registry or Nexus
  - Could be run in docker
    - `docker run -d -p 5000:5000 --restart=always --name registry registry:2` \
      `docker tag ubuntu:14.04 localhost:5000/mycompany/my-ubuntu:99` \
      `docker push localhost:5000/mycompany/my-ubuntu:99`
    - Storage could be localhost if backed up or AWS service or Google cloud registry or Azure
    - Saving / loading containers could be archived and move between storage types
      - `docker save -o my-images.tar.gz <image name> <image name>`
      - `docker load -i my-images.tar.gz`
    - Good for shipping by disk
- Orchestrating systems of containers
  - They start / restart containers
  - Service discovery to find containers
  - Resource allocation to match container to host in a pool
- Single machine simple way, docker compose
  - Good for testing and development with a simple command `docker compose up`
- K8s
  - Containers that run programs
  - Pods are groups of containers intended to run on a single host, pods move as a group
  - Services to make pods available to others as a group
  - Labels to describe services
  - Makes scripting large operations possible via kubectl
  - Very flexible overlay networking to allow pods to move around
  - As good from local as a cloud service
  - Built in service discovery
- ECS (AWS)
  - Task definitions
    : Defines sets of containers that always run together
  - Tasks
    : Actually makes the container run
  - Services and exposes to the network
  - Connects to other services like load balancers, EC2, S3, etc.
  - Provides docker repo as a built in
  - Containers and tasks can be part of CloudFormation
- Other options might be Fargate (AWS), Docker Swarm, Google / MS k8s versions
- EKS (AWS)
  - `kubectl get services`
  - Deploy something (getting started from AWS has an example)
  - Everything has replication controller then a number of services
  - Create the controller and then the services via cli with kubectl based on json files
  - `kubectl get services`
