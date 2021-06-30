FROM gcc
EXPOSE 80
COPY . /usr/src/hServ
WORKDIR /usr/src/hServ
RUN g++ --std=c++2a -pthread *.cpp
CMD ./a.out "$(hostname -i)"