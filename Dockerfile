FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qttools5-dev-tools \
    libgl1-mesa-dev \
    libxcb1-dev \
    libxcb-randr0-dev \
    libxcb-xinerama0 \
    libx11-xcb-dev \
    libglu1-mesa-dev \
    gdb \
    libpq-dev \
    libqt5sql5-psql \
    libqt5widgets5 \
    libqt5gui5 \
    libxrender1 \
    libxkbcommon-x11-0 \
    libxcb-shape0-dev

WORKDIR /app
COPY . /app

RUN qmake && make

ENV QT_X11_NO_MITSHM=1

CMD ["./ONIT", "-platform", "xcb"]