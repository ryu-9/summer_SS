# CODEX Handoff

## 概要

- 作業フォルダ: `C:\Users\nuhur\summer_SS`
- ゲーム本体: `Game\GameProject`
- ソリューション: `Game\GameProject.sln`
- 開発言語: C++
- ビルド環境: Visual Studio / MSVC `v143`
- ライブラリ: `DxLib` 同梱

このプロジェクトは、2D 対戦アクションにリズム要素を組み合わせたゲーム構成になっている。

## ディレクトリ構成の要点

- `Game\GameProject\source`
  - ゲーム本体コード
- `Game\GameProject\res`
  - UI、キャラ素材、モーション画像、SE、BGM、譜面 JSON、セーブデータなど
- `Game\Dxlib`
  - DxLib 関連ライブラリ群

確認時点のファイル数目安:

- `source`: 約 182 ファイル
- `res`: 約 911 ファイル

## 起動フロー

- エントリポイント: `Game\GameProject\source\winmain.cpp`
- `DxLib_Init()` 後に `Main` を生成
- `Game\GameProject\source\Main.cpp`
  - `Main::Init()` で初期サウンドや共通データを設定
  - `Main::RunLoop()` でゲームループを実行
  - シーン遷移を管理

## 主なシーン構成

`SceneType` は `Game\GameProject\source\Main.h` にある。

- `eTitle`
- `eMenu`
- `eOption`
- `eInstruction`
- `eCharaSelect`
- `eGameMain`
- `eDialogue`
- `eEnding`

主な対応ファイル:

- `Game\GameProject\source\SceneTitle.cpp`
- `Game\GameProject\source\SceneMenu.cpp`
- `Game\GameProject\source\SceneOption.cpp`
- `Game\GameProject\source\SceneSelect.cpp`
- `Game\GameProject\source\SceneMain.cpp`
- `Game\GameProject\source\SceneDialogue.cpp`
- `Game\GameProject\source\SceneEnding.cpp`

## コア構造の理解

### SceneBase

`Game\GameProject\source\SceneBase.h/.cpp`

- シーン共通基底
- アクタ、スプライト、ライト、FPS 制御、SE 制御、フェード、共通データを保持
- `_Tension` をシーン共通の値として保持
- `ChangeTension(int)` で `0..100` にクランプされる

現状の `_Tension` は、実質ゼロサム共有ゲージとして機能している。

### SceneMain

`Game\GameProject\source\SceneMain.cpp`

- 対戦本体
- `PlayerClass` 2体
- `RhythmControlClass`
- `EffectControlClass`
- `Stage`
- ソロ時は `AIControlClass`

現状の勝敗判定は HP ベース:

- どちらかの HP が 0 以下でラウンド終了
- 時間切れ時は HP 比率比較

### PlayerClass

`Game\GameProject\source\PlayerClass.h/.cpp`

- プレイヤー状態、モーション、被弾、ダメージ処理、当たり判定処理の中心
- 現状は `_HP` と `_MaxHp` を保持
- `GetHitPoint()` と `GetMaxHp()` が各所から参照されている
- 被弾やガードなどに応じて `_HP` 増減と `ChangeTension()` の両方が使われている

現状は「HP が本体、テンションが補助」の構造。

### RhythmControlClass

`Game\GameProject\source\RhythmControlClass.h/.cpp`

- BGM、譜面、ノーツ生成、観客や会場演出の制御
- `GetScene()->GetTension()` を使って、会場色やサイリウムの偏りを変えている

### UI

`Game\GameProject\source\PlayerUISpriteComponent.cpp`

- 現状のプレイヤー UI は HP バー前提
- `GetHitPoint()` / `GetMaxHp()` でバー長を計算
- キャラごとに HP マスク画像を切り替えている

### AI

- `Game\GameProject\source\AIProcessComponent.cpp`
- `Game\GameProject\source\AILerningProcessComponent.cpp`

AI は現状、HP とテンションの両方を状況判断に使っている。

## 現在確認できている HP / テンション依存箇所

### HP 依存が強い箇所

- `Game\GameProject\source\PlayerClass.h`
- `Game\GameProject\source\PlayerClass.cpp`
- `Game\GameProject\source\SceneMain.cpp`
- `Game\GameProject\source\PlayerUISpriteComponent.cpp`
- `Game\GameProject\source\AILerningProcessComponent.cpp`

### テンション依存が強い箇所

- `Game\GameProject\source\SceneBase.h`
- `Game\GameProject\source\SceneBase.cpp`
- `Game\GameProject\source\PlayerClass.cpp`
- `Game\GameProject\source\RhythmControlClass.cpp`
- `Game\GameProject\source\PsylliumControlClass.cpp`
- `Game\GameProject\source\Stage.cpp`
- `Game\GameProject\source\FlameClass.cpp`
- `Game\GameProject\source\AIProcessComponent.cpp`

## 実施済みの変更

以下のファイルに、挙動へ影響しない説明コメントのみ追加済み:

- `Game\GameProject\source\CameraClass.cpp`

ロジック変更は未実施。

## 改造の最終目標

- HP を廃止する
- 既存のテンションをゼロサム形式の主ゲージとして扱う
- HP の代わりにテンションを勝敗・UI・ダメージ評価の中心へ統一する

## 現時点で整理済みの改造方針

### 1. 勝敗判定を HP からテンションへ移す

対象:

- `Game\GameProject\source\SceneMain.cpp`
- `Game\GameProject\source\SceneMain.h`

必要な変更:

- ラウンド終了条件を HP 0 からテンション端到達へ変更
- 時間切れ時の優勢判定を HP 比率からテンション比較へ変更
- `_HPRatio` は削除または別指標へ置換

### 2. 被弾処理を HP 減算からテンション移動へ変える

主対象:

- `Game\GameProject\source\PlayerClass.cpp`

必要な変更:

- `_HP -= _Damage` 系を廃止
- 被弾結果を「相手側へテンションを押す」処理へ変更
- ガード、ジャストガード、投げ、ノーツ成否などのテンション変動量を再設計

### 3. UI を HP バー前提から変更する

対象:

- `Game\GameProject\source\PlayerUISpriteComponent.cpp`

必要な変更:

- `GetHitPoint()` / `GetMaxHp()` 依存の削除
- 共有テンションゲージ前提の描画へ変更
- 既存 HP マスク画像を流用するか、別演出へ差し替えるかは要判断

### 4. AI の状況認識を変更する

対象:

- `Game\GameProject\source\AILerningProcessComponent.cpp`
- 必要に応じて `Game\GameProject\source\AIStruct.h`

必要な変更:

- HP に依存した状況認識を廃止
- 共有テンションと優勢不利判定へ置換

### 5. 最後に Player から HP を取り除く

対象:

- `Game\GameProject\source\PlayerClass.h`
- `Game\GameProject\source\PlayerClass.cpp`

削除対象の候補:

- `_HP`
- `_MaxHp`
- `GetHitPoint()`
- `GetMaxHp()`

進め方としては、先に参照側を潰してから最後に削除する方が安全。

## 推奨実装順

1. 仕様を固定する
2. `SceneMain` の勝敗判定をテンション基準へ変更
3. `PlayerClass` の被弾処理をテンション基準へ変更
4. UI の HP 依存を解消
5. AI の HP 依存を解消
6. `PlayerClass` から HP メンバと API を削除
7. ビルドして残存参照をコンパイラエラーで洗い出す

## ユーザーと合意できている進め方

- 先にテンション中心の実装へ改造する
- その後 `Player` から HP を除去する
- 最後にビルドチェックで残存参照箇所を洗い出す

この方針は妥当で、段階ごとの確認もしやすい。

## 先に決めるべき仕様

未確定のため、着手前に定義した方がよい項目:

- `Tension == 0` がどちらの勝利状態か
- `Tension == 100` がどちらの勝利状態か
- 時間切れ時、`50` 基準の優勢判定でよいか
- ちょうど `50` の場合は引き分けか
- ラウンド開始時に毎回 `50` へ戻すか
- テンション移動量に現状 `_Damage` をそのまま使うか
- 旧 `_MaxHp` によるキャラ差を完全廃止するか、テンション補正に変換するか

## 注意点

- 今回の改造はコンパイル通過だけでは不十分
- とくに以下はビルド後の目視確認が必要
  - ラウンド終了条件
  - 時間切れ判定
  - 引き分け条件
  - UI 表示
  - AI の挙動
  - テンション増減の体感

## 次の作業候補

- HP 廃止後のルールを文章で固定する
- `SceneMain` の勝敗条件から改造を開始する
- `PlayerClass.cpp` の `_HP` 参照をテンション変換候補として一覧化する
