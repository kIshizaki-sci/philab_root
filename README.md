# Docker & Jupyter Labを用いたROOT解析環境

たった2行のコマンドでシステムから隔離された仮想コンピュータ上で使用できるROOT解析環境を立ち上げることができます．
この解析環境にはROOTの初歩的なチュートリアルが付いているので，学習&研究にご使用ください．

## 概要
宇宙・素粒子・原子核分野で使用されるデータ解析ソフトウェアROOTを使用するためのツールです．Windows, Mac (intel CPU限定．Apple Siliconは試験段階), Linux上で使用できます．このツールではJupyter Labを使用することでデータ解析手順の整理なども簡単に行えます．

本ツールは名古屋大 理学 物理 Φ研 院生の石崎によって，研究グループ内部での使用を前提に作成され，MITライセンスの元で配布されています．他の研究グループに適した環境で使用されたい場合はこのレポジトリをcloneするなりforkするなりして自由に改変してご使用ください．

## 前提条件
* x86処理系のコンピュータ．(2021年9月時点の場合，M1 Mac以外のパソコンは大体ok.)
* [git](https://git-scm.com/book/ja/v2/%E4%BD%BF%E3%81%84%E5%A7%8B%E3%82%81%E3%82%8B-Git%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB)
* [Docker](https://www.docker.com/products/docker-desktop)

gitはプログラム書いたりする人は皆使っているし，Dockerといったコンテナ技術はデータサイエンスやアプリ開発，クラウド関連など利用者も大変多いのでROOTとか関係なしにこれくらいは入れておきましょう．

Apple Siliconへの対応については試験段階です．上手く動いたら報告をおねがいします．

## Dockerを使う利点
[Docker](https://www.docker.com/)はDocker, Inc. が開発するコンテナ仮想化環境のプラットフォームです．仮想化とは各種テストやアプリケーション開発のためにコンピュータの中に別のバーチャルコンピュータを立ち上げることです．その中でもコンテナ技術は本格的な仮想化ではありませんが，軽量でかつ簡単に展開できる仮想化技術の1つになります．基本的にはコンテナの中で動くOSはLinuxになりますが，コンテナ自体はWindowsでもMac OSでもLinux上でも展開できます．最近ではCloud上でのサービスの構築，機械学習などにおいても重宝されており，コンピュータを扱う人間としては使えるべき能力の１つとなっています．

このツールではROOT解析環境をDockerコンテナ上に展開します．これには複数の利点があります．
* プロジェクト・解析環境・開発環境・データ・結果を1セットで管理可能．「新しいプロジェクトのためにソフトウェアをバージョンアップしたら昔のプロジェクトが動かなくなった」という事態を回避できます．
* レクチャーやスクールで環境導入に時間を割けない時に，コマンド数行で環境を展開できる．
* dockerfileを見ればどういった設定か分かる→トラブル解決時に参考になる．
* 新しい環境導入時に自身のマシンで上手く動かなくても簡単にロールバックできる．

逆に不利な点は
* コンテナ上でのGUIアプリケーションの扱いが面倒．(不可能では無いけど．)
ということがあります．ROOTは別ウィンドウを使うコードも多いので，その点には注意してください．

## ROOTチュートリアルのはじめ方

1. (入れていなければ)[Docker](https://www.docker.com/products/docker-desktop)と[git](https://git-scm.com/book/ja/v2/%E4%BD%BF%E3%81%84%E5%A7%8B%E3%82%81%E3%82%8B-Git%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB)をインストール．[WindowsへのDockerインストール](https://docs.docker.jp/docker-for-windows/install.html)は若干めんどい．
2. PowerShell (Macならばターミナル)を開き，適当な場所に作業用ディレクトリ(ここでは`~/workspace`とする．)に移動する．このレポジトリをclone. その後作成したディレクトリの中に入る．
```bash
cd ~/workspace
git clone https://github.com/kIshizaki-sci/philab_root.git -t v0.01-beta your_root_project
cd your_root_project
```
3. docker-composeでコンテナ(Dockerによって作られる仮想環境)を立ち上げる．
```bash
docker-compose up
```
この際に13 GBのdocker imageをダウンロードします．手元の計算機の容量と通信量に注意してください．
4. Google Chromeなどのwebブラウザからコンテナ中のJupyter Labにアクセス．アドレスバーに[http://localhost:8890](http://localhost:8890)を入力.
5. readme.ipynbを開く．
6. 終了させる際はPowerShellにて"Ctrl + C"でJupyter Labを終了させる．このとき，コンテナ内のJupyter Labにおいて"output", "working" の外に出来たファイルやディレクトリはコンテナを閉じると同時に消去されます．

## 注意
このコンテナイメージはsudoのパスワードを平文で扱っています．セキュリティリスクの高い方法での使用は避けてください．

## Dockerについて
Dockerは`イメージ`を`コンテナ`に展開することで仮想環境を構築します．このイメージはweb上で公開されているものや`Dockerfile`の中に書かれているレシピを元に仮想環境を構築します．  
Dockerの細かい使い方は割愛します．ググってください．とりあえずこのツールでは~workspace/your_root_projectにて実行する以下のコマンドだけは把握しておいてください．
* コンテナの立ち上げ : `docker-compose up`
* コンテナの停止: `docker-compose stop` 
* コンテナの再スタート: `docker-compose start` 
* コンテナの削除: `docker-compose down` 

また使っていないDockerオブジェクトを削除したいときは[ここ](https://docs.docker.jp/config/pruning.html)なんかを参照してください．

## テスト環境
Apple Silicon (Arm64)搭載のMac, AMD製CPU搭載の計算機での動作テストは行っていません．

* Windows 10 Pro (21H1)
  - Docker Desktop on Windows 3.5.2 (on WSL2)
  - CPU : intel i5-8500
  - メモリ : 32 GB

## 更新履歴
* 2021 09/26 : v0.2
* 2021 09/17 : β版リリース．

## Resources
https://github.com/docker/buildx/issues/495  

## License
[MIT License](./LICENSE)
