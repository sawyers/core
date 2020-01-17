FROM centos:7 AS base

COPY ./data/* /usr/tmp/

RUN mkdir -p /iii /iiidb/software /iiidb/options/config /root/.aws && \
  mv /usr/tmp/secrets /root/.aws/credentials && \
  yum install -y $(cat /usr/tmp/yum_list) && \
  yum install -y python-pip && \
  pip install --upgrade pip==9.0.3 && \
  pip install -r /usr/tmp/requirements.txt && \
  aws s3 cp s3://iii-custconv/tech-image/Sierra50/Sierra_linux_RH7_5.0.0_14.tar.gz /iiidb/software && \
  rm /root/.aws/credentials && \
  cd /iiidb/software && \
  tar xzvf *.tar.gz && \
  rm *.tar.gz && \
  ./prepare_rawinst -a && \
  mv /usr/tmp/iiiconfig.main /etc/iiiconfig.main && \
  mv /usr/tmp/siteconfig.h /iiidb/options/config/siteconfig.h && \
  cd /usr/raw && \
  echo $(cat /usr/tmp/rawinst_response) | ./rawinst -e iiiinit iiiconfig kernel_setup && \
  /bin/csh -c "source /etc/iiiconfig.main && cd /iiidb/software/compile && bldsys -f -R"

FROM geerlingguy/docker-centos7-ansible as sierra

COPY --from=base /iiidb ./iiidb
COPY ./data/iiiconfig.main /etc/iiiconfig.main

RUN yum install -y epel-release && \
  yum install -y python-pip csh && \
  /bin/csh -c "source /etc/iiiconfig.main && bldsys IIIHOME IIIROOT" && \
  pip install --upgrade pip==9.0.3 && \
  pip install awscli