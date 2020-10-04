FROM mongo:4.0.8

RUN apt-get update -y
RUN apt-get remove mongodb-org -y

RUN apt-get install mongodb -y
RUN mkdir -p ./data/db
RUN service mongodb start -y

EXPOSE 27017
