# gem
考虑点分治

对于一个联通块，我们只需要处理路径经过分治重心 $c$ 的询问。

对于一个联通块，先遍历一遍。  
遍历时记录假如当前有 $i$ 个宝石，到分治重心 $c$ 最多能收集几个宝石。  
这样就能求出每个节点到 $c$ 最多能收集多少个宝石。

对于询问$x\rightarrow y$，$x\rightarrow c$ 收集的宝石是已知的，那么把询问离线，在遍历到 $y$ 时处理后半部分询问。

回答询问的这次遍历，需要记录假如以 $i$ 个宝石结束，前半部分走到 $c$ 时至少需要收集多少个宝石。  
对于每个询问，二分答案，若前半部分收集的宝石大于后半部分所需要的就说明答案可行。

总时间复杂度 $O(nlogn+qlogn)$。