# docker_dev_env
Dockerでの開発環境です．

https://docs.docker.jp/index.html  
https://hub.docker.com/repository/docker/ishizakiss/my_dev_env/general  

## build方法
```bash
docker build ./philab_root_base/ --progress=plain -t philab-root-base:20220128
docker build . --progress=plain
```

## コンテナ操作の基本

### 立ち上げ&削除
```{bash}
docker build -t base:0 ./  
docker run -it base:0 /bin/bash  
docker run -d -p 8889:8888 base:0 jupyter lab --no-browser --port=8888 --ip=0.0.0.0 --allow-root --NotebookApp.token=''  

docker run -d -p 8889:8888 --volume $PWD/workspace:/home/ishizaki/workspace base:0 jupyter lab --no-browser --port=8888 --ip=0.0.0.0 --allow-root --NotebookApp.token=''  
```

### DockerHubへのpush
```{bash}
docker push yourname/newimage
```

## コンテナ・イメージ・キャッシュの停止&削除

全コンテナ停止: `docker stop \$(docker ps -q)`  
全コンテナ削除: `docker rm \$(docker ps -q -a)`  
全イメージ削除: `docker rmi \$(docker images -q)`  
`docker system df`  
`docker builder prune`  

## Docker Composeの使い方

`docker-compose up -d`  
https://qiita.com/suin/items/19d65e191b96a0079417
