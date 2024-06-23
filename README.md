# 2024 I2P Final Project - Plants vs Zombies

## 遊戲模式
包含冒險模式及保齡球模式兩種

## 遊戲機制
冒險模式為種植植物獲得太陽並擊敗殭屍，保齡球模式則是透過打保齡球擊敗殭屍

## 植物種類
Sunflower, Twin Sunflower, Peashooter, Repeater, Gatlin Peashooter, SnowPea, wallnut, cherrybomb

## 植物動畫
透過PlantAnimation讀取其對應的植物的Sprite Sheet資料（幀數、每幀高度、每幀寬度）更新畫面形成動畫。由這些資料直接挖取需要的範圍，然後更新Image的bmp來達到畫圖的效果。為此在Engine中的Sprite跟Image添加了新的建構式。除此之外，也利用植物本身的animationIndex來讓PlantAnimation可以正確播出符合植物現況的動畫（例如被吃掉的堅果牆）

## 殭屍種類
basic, cone, bucket, newspaper, flag, football player

## 殭屍動畫
類似於植物動畫，一樣透過ZombieAnimation去取用對應殭屍的Sprite Sheet。殭屍本身則是利用自己的functions去刷新animationIndex（例如死亡、報紙破掉），之後由ZombieAnimation依對應的animationIndex作調整。死亡後則是會進入一個小迴圈將動畫跑完


## 保齡球動畫
為植物動畫和殭屍動畫的綜合體

## Sprite Sheet製作
透過gif 素材轉成png後，再自行將不同片段拼在一起。最後手動輸入相關數據到每個物件裡，因每個單位的長、寬、幀數都十分不統一

## Lawnmower
透過現有的Plant class去製作一個除草機。並讓其射出一個無限傷害的除草機已達到除草機跑出去的效果，可殺死整排的殭屍

## Shovel
shovel可讓玩家剷除種好的植物並獲得太陽

<style>
table th{
    width: 100%;
}
</style>
