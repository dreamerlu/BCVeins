# BCVeins开发文档 
本文档用于开发过程中各大模块的说明，便于扩展与排错。

## RSU模块
### 一级模块：TraCIDemoRSU11p
这个模块对应的是RSU应用层的业务逻辑，通过gates与其它一级模块相连接，因此通过向gate发送消息可以实现与其它模块之间的通信。其包括的子模块目前包括：
1. 二级模块：PoWModule模块
>该模块用于PoW相关的业务逻辑，主要包括合法Nonce值的寻找。该模块收到PoWRequest后，会执行PoW算法（即根据data，以随机化的方式查找到一个有效的nonce）；这里采用基于事件的风格进行PoW，其中PoWInterval参数可以用于配置执行每次常识的间隔，因此如果赋值为SHA256的执行时间，那么总的时间即是PoW算法的实际执行时间；在成功找到合法的nonce后，会通过PoWResponse消息通过gate发送给RSU应用层，此时TraCIDemoRSU11p显然可以获取到这个值，从而可以发送到控制器进行处理。其中所涉及的消息包括：
> 1. PoWRequest: PoW请求信号
> 2. PoWResponse: PoW回复信号
> 3. PoWResult: RSU应用层根据PoWModule的执行结果向控制器发送的消息
### 一级模块：交换机/Switch
这个模块模拟路边单元之间的网络通信，以交换机的形式作为RSU之间的传输介质，目前实现了单播和广播这两种功能。其涉及到的消息包括：
> 1. UnicastMessage: 单播信号
> 2. BroadcastMessage：广播信号
### 一级模块：控制器/Controller
这个模块目前实现了多个路边单元关于PoW竞争最终结果的确定机制。其涉及到的消息包括：
> 1. PoWPackingPermission：控制器认定PoWResult有效的消息

### Gates连接情况
> RSU Appl：
> >rsu.gateIn[0] <-- switch.gateOut[0]<br>
> >rsu.gateOut[0] --> switch.gateIn[0]<br>
> \<parent>.gateIn[0] --> appl.gateIn[0];<br>
> appl.gateOut[0] --> \<parent>.gateOut[0];<br>
> 
> Switch：
> >前0~n-1个gateIn/Out与rsu相连接<br>
> >第n（也就是说0~n-1个gate被占用了）个gateIn/Out与controller的唯一gateIn/Out相连接
> > 
> Controller：
> >与Switch的第n个gateIn/Out相连接

## 核心逻辑关系
核心逻辑：RSU的应用程序模块TraCIDemoRSU11p通过生成PoWRequest消息，将该消息发送给其子模块PoWModule后，PoWModule会不断触发PoW计算最终找到合法的nonce。在该过程中，如果有新的PoWRequest到来，会将其放入到队列中，从而避免上次未完成的PoW计算被打断。PoW计算过程中如果合法的nonce被找到，那此时PoWModule会发送PoWResponse消息给TraCIDemoRSU11p，而TraCIDemoRSU11p会将PoWResponse封装成PoWResult消息后再封装成UnicastMessage消息（接收方设置为-1以标明发送给Controller）后发送给Switch，Switch收到后会将该消息转发给Controller。由于Controller会收到多个RSU的封装后的PoWResult，因此会将第一个（通过set容器存储Block data）收到的PoWResult认定是有效的，会将其封装成PoWPackingPermission消息以标明这个消息的发送方拥有这个区块的打包权，而对非第一个出现的PoWResult则不会进行处理。当TraCIDemoRSU11p收到PoWPackingPermission消息后，将其链接成区块链。。。

