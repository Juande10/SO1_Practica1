FROM python:3.6.8-alpine3.9

LABEL MAINTAINER="Juan de Dios Molina <juandem95@gmail.com>"

ENV GROUP_ID=1000 \
    USER_ID=1000

WORKDIR /var/www/

ADD ./requirements.txt /var/www/requirements.txt
RUN pip install -r requirements.txt
ADD . /var/www/

RUN pip install requests

RUN addgroup -g $GROUP_ID www
RUN adduser -D -u $USER_ID -G www www -s /bin/sh

USER www

EXPOSE 5000

CMD ["python", "app.py"]
