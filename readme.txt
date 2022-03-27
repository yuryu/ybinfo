-------------------------------------------------------------------------------
  Yuryu's Bettery Information         Version 1.3
                                      Copyright 2008 Yuryu / Emma Haruka Iwao
-------------------------------------------------------------------------------

・はじめに
    ダウンロードありがとうございました。
    このソフトウェアは、パソコンに搭載されているバッテリデバイスの、詳細情報
    を表示します。
    普段知らなかった、バッテリの一面を発見できるかもしれません。

・動作環境
    Windows 2000, XP またはそれ以降の Windows で動作します。
    Windows Vista + SP1 で動作確認しています。
    Windows 9x, Me, NT 3.x, 4 では動作しません。

・使用方法
    起動すると、画面が表示されて、情報が表示されます。
    「電池を選んでください」というところで、バッテリを選べます。
    また、更新をクリックすると、情報が更新されます。
    自動で更新したい場合は、自動更新のところに秒数を入力してください。
    ０秒にすると更新されなくなります。
    F1 キーを押すとバージョン情報が表示されます。

・表示される情報について
    Windows 2000以降に用意されている電源管理APIを使用しています。
    デバイスが知らない情報は「不明」とでます。
    情報の内容は、見ればだいたいわかると思いますので、解説は省略。

・アイコンについて
    謎のアイコンではなく、でんちの「で」を抽象化したものです。

・ソースについて
    開発環境は Visual Studio 2008 です。
    Mercurial レポジトリが以下の URI で利用可能です。

    https://holo.wotax.net/~hg/pub/YbInfo/

・ライセンス
    Apache License, Version 2.0 にて配布します。

    Yuryu's Battery Information, displays detailed battery info.
    Copyright 2008 Yuryu / Emma Haruka Iwao

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Read the LICENSE file for more info.

・バージョンアップにおける変更点

   Ver.x.x  ・ライセンスを Apache License, Version 2.0 に変更しました。
   Ver.1.3  ・文字情報を取得する際に、バッファをゼロクリアしてから取得するよう
              変更しました（文字化けが発生することがあった）。
            ・自動更新秒数を入れるのテキストボックスの文字を消すと
              エラーが出るのを修正しました
   Ver.1.2  ・開発環境を Visual Studio 2008 に変更しました。
            ・ライセンスを GPL v3 に変更しました。
            ・バッテリのタグが取得できないときに、5秒待ってタイムアウトする
            　ようにしました（昔は無限に待っていました）。
            ・Unicode アプリケーションとなりました。
   Ver.1.1  ・バッテリの番号が０から始まっていない場合に正しく認識
              されなかった問題を解決（したつもりですが、検証できてません）。
            ・連絡先が間違っていた and 変わったので、書き換えました。
            ・開発環境が VS.Net 2003 になりました。
            ・MFC を静的リンクしたため、DLLが不要になりました。
            ・F1 でバージョン情報が表示されるようにしました。
            ・自動更新モードを追加しました。
            

・連絡先など
    Web     http://www.wotax.net/
    E-mail  yuryu@wotax.net

