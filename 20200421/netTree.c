//
// Created by YangHui on 2021/5/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LOCAL

typedef enum Enum_DeviceType
{
    Switches, Computer, Printer
} DeviceType;
typedef struct Struct_Device
{
    int id;
    DeviceType type;
    struct Struct_Device *parent;
    struct Struct_Device *child[8];
    int priority;

    int depth;
    int track[128];
    int trackLen;
} Device;

Device *deviceArray[1024];
int deviceArrayTop = 0;
Device *getDevice(int id);
Device *insertNet(int id, int type, int parent, int portNum);
void findTrack(int *device, int id);
void copyTrack(int *dest, int *src, int num);
void buildPriority(Device *root, int *num);

int main()
{
    // 读入数据
#ifdef LOCAL
    FILE *input = stdin;
#else
    FILE *input = fopen("in.txt", "r");
#endif
    if (input == NULL)
        return 0;
    int deviceNum, computerNum;
    scanf("%d %d", &deviceNum, &computerNum);
    int id, type, parent, portNum;
    Device *root = NULL;
    for (int i = 0; i < deviceNum; i++)
    {
        fscanf(input, "%d %d %d %d", &id, &type, &parent, &portNum);
        Device *newDevice = insertNet(id, type, parent, portNum);
        if (parent == -1)
            root = newDevice;
        deviceArray[deviceArrayTop++] = newDevice;
    }
    int num = 0;
    buildPriority(root, &num);
    int device;
    findTrack(&device, computerNum);
    Device *target = getDevice(device);
    printf("%d ", target->track[target->trackLen - 1]);
    for (int i = 1; i < target->trackLen - 1; i++)
        printf("%d ", target->track[i]);
    return 0;
}

Device *insertNet(int id, int type, int parent, int portNum)
{
    Device *newDevice = (Device *) calloc(1, sizeof(Device));
    if (parent == -1) // 表明属于根节点设备
    {
        newDevice->id = id;
        newDevice->type = type;
        return newDevice;
    }
    else
    {
        newDevice->id = id;
        newDevice->type = type;
        newDevice->parent = getDevice(parent);
        getDevice(parent)->child[portNum] = newDevice;
        return newDevice;
    }
}

Device *getDevice(int id)
{
    for (int i = 0; i < deviceArrayTop; i++)
    {
        if (deviceArray[i]->id == id)
            return deviceArray[i];
    }
    return NULL;
}

void findTrack(int *deviceID, int id)
{

    Device *start = getDevice(id)->parent;
    start->depth = 1; // 初始的节点深度是1
    Device *findQueue[1024] = {0};
    int visited[1024] = {0};
    int track[512] = {0};
    int trackTop = 0;
    Device *device[512] = {0};
    int deviceTop = 0;
    int queueHead = 0, queueRear = -1;
    findQueue[++queueRear] = start;
    // 首先插入计算机和它的上一层交换机
    track[trackTop++] = id;
    copyTrack(start->track, track, trackTop);
    start->trackLen = trackTop;
    while (1)
    {
        Device *nowDevice = findQueue[queueHead++];
        copyTrack(track, nowDevice->track, nowDevice->trackLen);
        trackTop = nowDevice->trackLen;
        visited[nowDevice->id] = 1;
        int depth = nowDevice->depth;
        track[trackTop++] = nowDevice->id;

        // 首先遍历寻找是否有打印机
        for (int i = 0; i < 8; i++)
        {
            if (nowDevice->child[i] == NULL)
                continue;
            if (nowDevice->child[i]->type == Printer)
            {
                track[trackTop++] = nowDevice->child[i]->id;
                // 复制路径和深度
                copyTrack(nowDevice->child[i]->track, track, trackTop);
                nowDevice->child[i]->depth = depth;
                nowDevice->child[i]->trackLen = trackTop;
                // 回退路径
                trackTop--;
                // 标明访问
                visited[nowDevice->child[i]->id] = 1;
                device[deviceTop++] = nowDevice->child[i];
            }
        }

        // 如果没有发现打印机，那么就将它连接的节点一同载入
        for (int i = 0; i < 8; i++)
        {
            if (nowDevice->child[i] == NULL)
                continue;
            if (nowDevice->child[i]->type == Switches && visited[nowDevice->child[i]->id] == 0)
            {
                findQueue[++queueRear] = nowDevice->child[i];
                nowDevice->child[i]->depth = nowDevice->depth + 1;
                copyTrack(nowDevice->child[i]->track, track, trackTop);
                nowDevice->child[i]->trackLen = trackTop;
            }
        }
        if (nowDevice->parent != NULL && visited[nowDevice->parent->id] == 0)
        {
            findQueue[++queueRear] = nowDevice->parent;
            nowDevice->parent->depth = nowDevice->depth + 1;
            copyTrack(nowDevice->parent->track, track, trackTop);
            nowDevice->parent->trackLen = trackTop;
        }

        // 如果队列为空，退出循环
        if (queueHead > queueRear)
            break;
    }

    int depth, pri;
    for (int i = 0; i < deviceTop; i++)
    {
        if (i == 0)
        {
            depth = device[i]->depth;
            pri = device[i]->priority;
            *deviceID = device[i]->id;
        }
        if (device[i]->priority < pri && device[i]->depth == depth)
        {
            pri = device[i]->priority;
            *deviceID = device[i]->id;
        }
        else
            continue;
    }
    return;
}

void buildPriority(Device *root, int *num)
{
    if (root == NULL)
        return;
    for (int i = 0; i < 8; i++)
    {
        buildPriority(root->child[i], num);
    }
    root->priority = (*num)++;
}

void copyTrack(int *dest, int *src, int num)
{
    for (int i = 0; i < num; i++)
        dest[i] = src[i];
}
