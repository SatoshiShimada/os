オリジナル　オペレーティングシステム
====

Target: x86 IntelArchitecture 32bit

## 概要

### 使用　開発環境

* エミュレータ: qemu(version 2.2.1)

* コンパイラ: gcc(version 4.9.2)

* 開発ホストOS: Linux

* 想定しているストレージ: フロッピーディスク

### 使用方法

ワーキングディレクトリをソースコードのあるディレクトリにする

そして、makeとmake runでエミュレータが起動してOSが実行される

`make`

`make run`

フロッピーディスクに書き込みたい場合はmakeして出来た'os.img'ファイルを

ddコマンドなどでフロッピーディスクに書き込む

`make`

Exsample)

`dd if=./os.img of=/dev/sdx bs=512 count=2880 conv=sync,trunc`

### メモ

ファイルシステム: FAT12

マスターブートレコーダ: 0xC200にジャンプしてFDDの2セクター目からのプログラムを実行する

2セクター目からのプログラムでProtectedMode(32bit)に移行する

その後、C言語で書いたmain関数をコールする

## メモリマップ
0x8200: sector2(file: stage2.bin)

0xc200: 0x4200 of FDD image (file: stage2.bin)

## 実装済みの機能

* Protected Modeへの移行

* 割り込みの処理

* キーボードからのキーコード取得

* FAT12ファイルシステムからのファイル名取得

* 搭載メモリ量の確認

## 実装予定

* TaskSwtich

* メモリー管理

* FileSystem: FAT12

* The text editor(like vi)

## 既知のバグ

* コマンドの途中でエミュレータが異常終了する