#Docker container for Aerostack

##Introduction

Docker is a platform to develop, deploy, and run applications with containers. The use of Linux containers to deploy applications is called containerization. Docker performs operating-system-level virtualization. Docker can package an application and its dependencies in a virtual "container" that can run on any Linux server. This helps enable flexibility and portability on where the application can run.

Containerization is increasingly popular because containers are:

* Flexible: Even the most complex applications can be containerized.
* Lightweight: Containers leverage and share the host kernel.
* Interchangeable: You can deploy updates and upgrades on-the-fly.
* Portable: You can build locally, deploy to the cloud, and run anywhere.
* Scalable: You can increase and automatically distribute container replicas.
* Stackable: You can stack services vertically and on-the-fly.

A container is launched by running an "image". A Docker image is a read-only template used to build containers. An image is an executable package that includes everything needed to run an application--the code, a runtime, libraries, environment variables, and configuration files. Images are used to store and ship applications. Containers are created from "images" that specify their precise contents.

A Docker "container" is a standardized, encapsulated environment that runs applications. A container is managed using the Docker API or CLI (command line interpreter). A container is a runtime instance of an image--what the image becomes in memory when executed (that is, an image with a state, or a user process).  Containers are run by a single operating system kernel and are more lightweight than virtual machines. 

To become familiar with Docker environment you can consult the following documentation:

* [Start with Docker](https://docs.docker.com/get-started/)

##Preparation

If Docker isn't installed in your computer, please install it:

* [Docker installation](https://docs.docker.com/install/#supported-platforms)

When Docker is installed, if you would like to use it as a non-root user, you should now consider adding your user to the “docker” group (remember to log out and back in for this to take effect).

Clone in your working directory the following repository:
    
     $ git clone https://bitbucket.org/visionaerialrobotics/building_docker_aerostack/src/master/

>> Actualizar url del repositorio de bitbucket cuando se suba el definitivo

It includes the following scripts:

* `build.sh`: Creates the docker image, it adds support for gpu if requested. This script accepts the following parameters:

    ```$ ./build.sh <dockerfile_dir> <git_url> [<image_name> <gpu_support>]```

* `start.sh`: Starts the Docker image and sets everything up (i.e.: volumes, bound ports, and workspace). This script accepts the following parameters:

    ```$ ./start.sh <working_dir> <image_name> [<instance_name> <gpu_support>]```

* `launch.sh`: Launches the Docker image and gets you inside it. This script accepts the following parameters. 

    ```$ ./launch.sh <container_name> [<zsh> (default:true)]```

* `stop.sh`: Stops a running container 

You need to use `sudo` to execute the following Docker commands in a terminal window.

#Instructions for developers who want to create an image

Docker Hub is a service provided by Docker for finding and sharing container images with your team. Currently, the account that Aerostack uses in Docker is `visionaerialrobotics` in which there are repositories of different Aerostack versions. 

The following steps describe how to build a Docker image from Aerostack repository on Github with version 2.1 and to push it in Docker:

* Execute build.sh script to build the Docker image:

    ```$ ./docker-aerostack/scripts/build.sh /docker-aerostack/aerostack https://github.com/Vision4UAV/Aerostack aerostack_v2.1```

* Check that the image was built successfully:

    ```$ sudo docker images```

would return the repository name `aerostack_v2.1` and its details (may be different from yours): 

    REPOSITORY          TAG         IMAGE ID        CREATED         SIZE
    aerostack_v2.1      latest      8a3bf7598121    1 minute ago    6.06GB

* In Docker, an image name is made up of slash-separated name components. Create a tag `visionaerialrobotics/aerostack_v2.1` that refers to `aerostack_v2.1`:

    ```$ sudo docker tag aerostack_v2.1:latest visionaerialrobotics/aerostack_v2.1```

* Log in to Docker:
 
    ```$ sudo docker login```

* Push Docker image:

    ```$ sudo docker push visionaerialrobotics/aerostack_v2.1 ```

You can build a docker image with other version of Aerostack. For example, an image from Aerostack current private repository on Bitbucket. You need your Bitbucket credentials and the corresponding user rights. Let's give a fictitious user of Bitbucket as an example:

    User: myuser
    Password: mypass

Then, build the Docker image, named my_aerostack. Excute the following command:

```
$ ./docker-aerostack/scripts/build.sh ./docker-aerostack/aerostack https://myuser:mypass@bitbucket.org/Vision4UAV/aerostack.git my_aerostack
```

Use `$ sudo docker images` command to check that the image was built successfully. 

>> ¿Enlace a ##Creating the container al terminar esta seccion?

#Instructions for users of an image

##Downloading Aerostack image

The `pull` command fetches the Aerostack image from the Docker registry and saves it to our system. To get started, let's run the following command in a terminal window:

```sh
$ sudo docker pull visionaerialrobotics/aerostack_v2.1
```

Next, to check that the image was downloaded successfully:

```sh
$ sudo docker images
```

would return the container name `visionaerialrobotics/aerostack_v2.1` and its details (may be different from yours) : 

    REPOSITORY                              TAG                 IMAGE ID            CREATED             SIZE
    visionaerialrobotics/aerostack_v2.1     latest              8a3bf7598121        23 hours ago        6.06GB


##Creating the container

To create the container with the necessary volumes and devices mounted to Aerostack works, use the `start.sh` script:

```sh
$ ./docker-aerostack/scripts/start.sh . visionaerialrobotics/aerostack_v2.1 aerostack_v2.1_container
```

Next, to check that the container `aerostack_v2.1_container` was created successfully:

```sh
$ sudo docker ps -l
```

    CONTAINER ID        IMAGE                                 COMMAND                  CREATED              STATUS              PORTS                      NAMES
    8c59d3453f1b        visionaerialrobotics/aerostack_v2.1   "/ros_entrypoint.s..."   About a minute ago   Up About a minute   0.0.0.0:11392->11311/tcp   aerostack_v2.1_container

Besides, to check that the following directories are in your current directory: `workspace`, `catkin_ws`, `gazebo_ws`.

The workspace directory specifies where to create workspace for the container. It is always mounted as a volume for Docker to ensure persistence beyond the container's lifetime. 

##Using the container

To get inside of the container, you can write the following command:

```sh
$ sudo docker exec -it <container_name> bash
```

If you are going to use any application that depends upon a GUI (like many parts of the Aerostack or any non-headless simulator), you must launch the container through the `launch.sh` script, which sets up the necessary authentication with the X11 server.

```sh
$ ./docker-aerostack/scripts/launch.sh aerostack_v2.1_container
```

>>¿Dejar ambas opciones, o sólo la segunda?

###First Usage

If the workspace has just been created (i.e., it is the first time you use it), it is necessary to call `/root/setup.sh`, which installs the rest of the Aerostack from a git repository, this includes drones' drivers and a lot more stuff. This step is necessary for every different `working_dir` given to the start script, so if you are reusing a workspace you should do this only the first time. The steps are as follows:

```sh
# source ros and bashrc
$ source ros_entrypoint.sh
$ source /root/post_install.sh https://github.com/Vision4UAV/Aerostack 
```

Please note that if you have Aerostack in your own private repo (private fork, for example) you have to pass a url with the correct credentials, something in the form: https://[user:pass@]github.com/Vision4UAV/Aerostack

After this step, you should be able to compile:

```sh
$ cd $AEROSTACK_WORKSPACE
$ catkin_make
```

Also, to check that the repository is okay you can try launching a mission:

```sh
$ cd $AEROSTACK_STACK
$ source ./setup.sh
$ ./launchers/simulated_quadrotor_basic.sh 
```

#OS supported

This has been tested in Linux (Ubuntu).

Windows is not based on Unix so there is no way to bind devices. If you are using Windows, just install a Linux distro or a virtual machine.

Running over MacOS could work, but there are certain caveats. In general, Linux handles hardware access through the use of sockets, the start script handles this for you automatically in Linux hosts, but it should be tested on MacOS, as a general intro:

* GUI Applications: In order for any Docker image to create GUI applications it needs to have access to the X11 server socket, in Linux systems this is stored in `/tmp/.X11-unix/`. The start script does this for you automatically for Linux hosts. If you are able to make this work, please fill an issue or PR so we can update the repository for the next users.
* Sound Applications: For any application to produce sound it needs access to the sound card (hardware or virtual), this is usually handled through a special device allocated in /dev/snd, how is it handled on MacOS?