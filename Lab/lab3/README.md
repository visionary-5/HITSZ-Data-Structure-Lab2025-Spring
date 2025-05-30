# HITSZ 数据结构实验三: 排序算法&动态规划实验

## 一、疯狂的采药

### 题目描述

药童Li去山洞采药，山洞里有一些不同种类的草药，每种草药可以无限制的疯狂采摘。采每一种草药都需要一些时间，每一种草药也有它自身的价值。给Li一段时间，在这段时间里，让采到的草药的总价值最大。

### 输入描述

第一行有两个整数，分别代表总共能够用来采药的时间C和代表山洞里的草药数目n;  
第二行到第n+1行，每行两个整数，第（i+1）行的整数ci和wi，分别表示采摘第i种草药的时间和该草药的价值。

### 输出描述

一行，一个整数，表示在规定时间内可以采到的草药的最大总价值。

### 输入样例

```c
70 3
71 100
69 1
1 2
```

### 输出样例

```c
140
```

## 二、数字映射排序

### 题目描述

给你一个下标从 0 开始的整数数组 mapping ，它表示一个十进制数的映射规则，mapping[i] = j 表示这个规则下将数位 i 映射为数位 j 。一个整数映射后的值为将原数字每一个数位 i （0 <= i <= 9）映射为 mapping[i] 。另外给你一个整数数组 nums ，请你将数组 nums 中每个数按照它们映射后对应数字非递减顺序排序后输出。

### 注意

如果两个数字映射后对应的数字大小相同，则将它们按照输入中的相对顺序排序。nums 中的元素只有在排序的时候需要按照映射后的值进行比较，返回的值应该是输入的元素本身。

### 输入样例

```c
3
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
[321, 123, 213]
```

### 输出样例

```c
[123, 213, 321]
```

## 三、信封套娃

### 题目描述

定义一个信封为 [w, h] ，其中 w 表示宽度， h 表示高度。定义一个信封 [w1, h1] 可以装进另一个信封 [w2, h2] ： w1 < w2 且 h1 < h2 。现在有若干个这样的信封，请你计算最多有多少个信封可以组成一组这样的“套娃”序列。

### 输入样例

```c
4
5 4 6 4 6 7 2 3
```

### 输出样例

```c
3
```

## 四、字符频率排序

### 题目描述

给定一个字符串 s ，根据字符出现的频率对其进行降序排序。一个字符出现的频率是它出现在字符串中的次数。若两个字符出现的频率相同，则按照 ASCII码从小到大进行排序。s 中只包含大写字母和小写字母。

### 输入样例

```c
AaddBcd
```

### 输出样例

```c
dddABac
```
