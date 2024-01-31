# 注意
结合inet 4.3.5
# 记录
1. 在实现PoW时，由于是采用事件的模拟，因此是不断验证nonce的合法性不断更新Nonce,一直到nonce是有效的为止。为此可以将其中的尝试间隔interval设置为HASH的计算时间，这样完整的尝试过程所需要的时间,实际上也就是真实的PoW计算时间。

# ToDo

区块链相关的参数需要设置：
1. PoWInterval：计算PoW中SHA的间隔；
2. PoWDifficulty:计算PoW中难度（2进制），因此最大不能超过256；