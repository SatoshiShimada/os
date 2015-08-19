オリジナル　オペレーティングシステム
====

Target: x86 IntelArchitecture 32bit

## 概要

アセンブリ言語とC言語で開発

Linux環境で作業

実機ではなくエミュレータで動作確認

### 使用　開発環境

* エミュレータ: qemu(version 2.0.0 or 2.2.1 or 2.3.0)

* コンパイラ: gcc(version 4.9.2 or 5.1.0)

* 開発ホストOS: Linux(Arch Linux)

* 想定しているストレージ: フロッピーディスク

* 必要なコマンド

** `mformat` `mcopy`
pacman -S mtools でインストール可能(ArchLinux)

** `gcc objcopy` (GNU Binary Utilitys)

### 使用方法

ワーキングディレクトリをソースコードのあるディレクトリにする

そして、makeとmake runでエミュレータが起動してOSが実行される

`make`

`make run`

フロッピーディスクに書き込みたい場合はmakeして出来た'os.img'ファイルを

ddコマンドなどでフロッピーディスクに書き込む

`make`

Example)

`dd if=./os.img of=/dev/sdx bs=512 count=2880 conv=sync,trunc`

### メモ

ファイルシステム: FAT12

カーネルとシェルを分けて考える？

CUI, GUIで動作する

ビデオドライバ、テキストモードに対応させる

マスターブートレコーダ: 0xC200にジャンプしてFDDの2セクター目からのプログラムを実行する

2セクター目からのプログラムでProtectedMode(32bit)に移行する

その後、C言語で書いたmain関数をコールする

Secondly, setup IDT initialize, then PIC & PIT initialize.

Fainaly, variable initialize, then allow interrupt & screen initialize & command mode.

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

* GUI画面の搭載(高解像度)

* TaskSwtich(マルチタスク)

* メモリー管理

* FileSystem: FAT12(ファイル書き込み)

* The text editor(like vi)

## 既知のバグ

* exeコマンドの途中でエミュレータが異常終了する (アドレス指定のミス？)
