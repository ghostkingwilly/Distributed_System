
HW2a.

1. programming language: C++
2. 用ifstream讀檔  fin.open("test1.txt"); //直接改檔名
3. 在 console block 顯示結果
4. 經實驗結果得，與HW1結果一樣
5. 會對每次結果進行比較並顯示所有結果及機率

HW2b.

1. programming language: C++
2. 用ifstream讀檔  fin.open("test1.txt"); //直接改檔名
3. 在 console block 顯示結果
4. 第一組測資會卡住，因為在random assign 給set 的時候，相同W(v) / (deg(v) + 1) 可能同時存在或不存在 set，導致不斷更改互相的資訊進入無限迴圈
5. 第二組測資都會跑完並顯示出結果，但發現都是相同的解
6. 會對每次結果進行比較並顯示所有結果及機率，第一組結果正確

HW2c.

1. programming language: C++
2. 用ifstream讀檔  fin.open("test1.txt"); //直接改檔名
3. 在 console block 顯示結果
4. 兩組測資都會跑完並顯示出結果，但發現都是相同的解
5. 會對每次結果進行比較並顯示所有結果及機率，第一組與第二組結果不一定是對的，因為相同W(v) / (deg(v) + 1)鄰居可能一開始就加到MIS裡面

HW2d.

若遇到相同W(v) / (deg(v) + 1)的鄰居時就 random 決定一個人進到 MIS set中