# chrome_history_searcher

## 概要

Chrome(Firefoxに互換性あり?)の閲覧履歴を表示・検索・分析するためのツールです。

## 使い方

Windows : /Users/自分のディレクトリ/Library/Application Support/Google/Chrome/Default/History

Mac : /Users/自分のディレクトリ/Library/Application Support/Firefox/Profiles/ユーザーごとに固有の値.default/places.sqlite

ChromeOS : 開発者モードに移行後、ホームディレクトリからHistoryファイルを入手可能

データベースのファイルは、これらのファイルを**必ずコピーして**使用してください。

コマンド起動時は、 chrome_history "Database name" で起動できます。

|機能名|説明|
|--|--|
|0.Exit|プログラムの終了|
|1:search|URL,タイトルから検索|
|2:count|ドメインごとにカウント|

## 参考記事

https://qiita.com/maeharin/items/a2fb6242d26555c85dec - ブラウザの閲覧履歴で人生の棚卸し（embulk + elasticsearch + kibanaで可視化） #Elasticsearch - Qiita 
