# Chrome history searcher (CHS)

## 概要

Chrome(Firefoxに互換性あり?)の**閲覧履歴を表示・検索・分析**するためのツールです。

略称はイニシャルを取ってCHSにしています。(一応)

## How to build

このプログラムをコンパイルするには、SQLite3の開発ライブラリが必要です。

```bash
#On Ubuntu/debian
sudo apt update
sudo apt install libsqlite3-dev

sudo apt install libreadline-dev
```

その後、以下のコマンドでコンパイルし、実行ファイルを生成します。

```bash
gcc main.c count.c search.c -o chrome_history -lsqlite3 -lreadline
```

## 使い方

Windows : ```/Users/自分のディレクトリ/Library/Application Support/Google/Chrome/Default/History```

Mac : ```/Users/自分のディレクトリ/Library/Application Support/Firefox/Profiles/ユーザーごとに固有の値.default/places.sqlite```

ChromeOS : ```/home/chronos/user/History``` (開発者モードへの移行が必要)

データベースのファイルは、これらのファイルを**必ずコピーして**使用してください。

コマンド起動時は、 ```chrome_history "Database name"``` で起動できます。

|機能名|説明|
|--|--|
|1.Exit|プログラムの終了|
|2:search|URL,タイトルから検索|
|3:count|ドメインごとにカウント|

```ctrl+D```でも終了できます。

## その他・参考記事
このコードの生成について、一部Gemini等AIの回答を参考にしています。

https://qiita.com/maeharin/items/a2fb6242d26555c85dec - ブラウザの閲覧履歴で人生の棚卸し（embulk + elasticsearch + kibanaで可視化） #Elasticsearch - Qiita 
