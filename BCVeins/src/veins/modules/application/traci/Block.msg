//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
import veins.modules.messages.BaseFrame1609_4;
namespace veins;
packet Block extends BaseFrame1609_4
{
    // 区块头
    string previousBlockHash;  // 前一个区块的哈希值
    simtime_t timestamp;       // 时间戳
    int difficultyLevel;       // 难度等级
    string miner;              // 挖矿者
    int nonce;                 // Nonce（随机数）

    // 区块体
    string transactionData;    // 包含交易数据
}