IMG=python:3
CMD=python
ARG=main.py
DIR=/usr/src/myapp
##
# docker run \            # Run a command in a new container
#     -it \               # allocate a pseudo-TTY connected to the container’s stdin
#     --rm \              # Automatically remove the container when it exits
#     --name ${ARG} \     # container designation
#     -v "$PWD":${DIR} \  # mount volume
#     -w ${DIR} \         # working directory
#     ${IMG} \            # docker image
#     ${CMD} ${ARG}       # command argument
##
docker run \
    -it \
    --rm \
    --name ${ARG} \
    -v "$PWD":${DIR} \
    -w ${DIR} \
    ${IMG} \
    ${CMD} ${ARG}
