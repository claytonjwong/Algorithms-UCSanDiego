EXE=main.py
DIR=/usr/src/myapp
docker run -it --rm --name ${EXE} -v "$PWD":${DIR} -w ${DIR} python:3 python ${EXE}
