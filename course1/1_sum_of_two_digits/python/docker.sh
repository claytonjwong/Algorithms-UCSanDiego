IMAGE=python:3
CMD=python
ARG=APlusB.py
DIR=/usr/src/myapp
docker run \
    -it \
    --rm \
    --name ${ARG} \
    -v "$PWD":${DIR} \
    -w ${DIR} \
    python:3 \
    ${CMD} ${ARG}
