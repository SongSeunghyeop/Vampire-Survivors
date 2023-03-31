#include "Enemy1.h"
#include "EnemyPool.h"

namespace my
{
        EnemyPool::EnemyPool(int poolSize)
        {
            for (int i = 0; i < poolSize; i++) //�μ� ���� ��ü ������ ��ŭ ���ʹ� ���� ����
            {
                pool.push_back(new my::Enemy1());
            }
        }
        EnemyPool::~EnemyPool()
        {
            for (auto enemy : pool)
            {
                delete enemy;
            }
        }

        my::Enemy1* EnemyPool::GetEnemy()
        {
            if (index >= pool.size()) //
            {
                index = 0;
            }

            return pool[index++];
        }
}