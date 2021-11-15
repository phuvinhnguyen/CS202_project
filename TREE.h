#ifndef TREE
#define TREE
#include "header.h"

class Tree
{
private:
    struct node
    {
        vector<OXY> data;
        node *upleft, *upright, *downleft, *downright;

        node(OXY ndata)
        {
            data.push_back(ndata);
            upleft = upright = downleft = downright = nullptr;
        }

        node(vector<OXY> ndata)
        {
            data = ndata;
            upleft = upright = downleft = downright = nullptr;
        }

        ~node()
        {
            delete upright;
            delete upleft;
            delete downright;
            delete downleft;
        }
    };

    // DATA
    node *head;
    const int MAX = 5;

public:
    Tree() : head(nullptr) {}

    void insert(OXY point)
    {
        if (point.x < 0 || point.x > ConsoleWidth || point.y < 0 || point.y > ConsoleHeight)
            throw("Tree error: insert out of range point");

        if (head == nullptr)
        {
            head = new node(point);
            return;
        }

        node *tm = head;
        OXY upleft(0, 0), downright(ConsoleWidth, ConsoleHeight);
        while (tm->upleft != nullptr)
        {
            if (point.x < (upleft.x + downright.x) / 2)
            {
                if (point.y < (upleft.y + downright.y) / 2)
                {
                    tm = tm->upleft;
                    downright.x -= ((downright.x - upleft.x) / 2);
                    downright.y -= ((downright.y - upleft.y) / 2);
                }
                else
                {
                    tm = tm->downleft;
                    upleft.y += ((downright.y - upleft.y) / 2);
                    downright.x -= ((downright.x - upleft.x) / 2);
                }
            }
            else
            {
                if (point.y < (upleft.y + downright.y) / 2)
                {
                    tm = tm->upright;
                    upleft.x += ((downright.x - upleft.x) / 2);
                    downright.y -= ((downright.y - upleft.y) / 2);
                }
                else
                {
                    tm = tm->downright;
                    upleft.x += ((downright.x - upleft.x) / 2);
                    upleft.y += ((downright.y - upleft.y) / 2);
                }
            }
        }

        for (int i = 0; i < tm->data.size(); i++)
        {
            if (point == tm->data[i])
                return;
        }

        if (tm->data.size() < MAX)
        {
            tm->data.push_back(point);
        }
        else
        {
            vector<OXY> upleftnode, uprightnode, downleftnode, downrightnode;
            for (int i = 0; i < tm->data.size(); i++)
            {
                if (point.x < (upleft.x + downright.x) / 2)
                {
                    if (point.y < (upleft.y + downright.y) / 2)
                        upleftnode.push_back(tm->data[i]);
                    else
                        downleftnode.push_back(tm->data[i]);
                }
                else
                {
                    if (point.y < (upleft.y + downright.y) / 2)
                        uprightnode.push_back(tm->data[i]);
                    else
                        downrightnode.push_back(tm->data[i]);
                }
            }

            tm->data.clear();
            tm->downleft = new node(downleftnode);
            tm->downright = new node(downrightnode);
            tm->upleft = new node(upleftnode);
            tm->upright = new node(uprightnode);
        }
    }
    void remove(OXY point)
    {
        if (point.x < 0 || point.x > ConsoleWidth || point.y < 0 || point.y > ConsoleHeight)
            return;

        node *tm = head;
        OXY upleft(0, 0), downright(ConsoleWidth, ConsoleHeight);
        while (tm->upleft != nullptr)
        {
            if (point.x < (upleft.x + downright.x) / 2)
            {
                if (point.y < (upleft.y + downright.y) / 2)
                {
                    tm = tm->upleft;
                    downright.x -= ((downright.x - upleft.x) / 2);
                    downright.y -= ((downright.y - upleft.y) / 2);
                }
                else
                {
                    tm = tm->downleft;
                    upleft.y += ((downright.y - upleft.y) / 2);
                    downright.x -= ((downright.x - upleft.x) / 2);
                }
            }
            else
            {
                if (point.y < (upleft.y + downright.y) / 2)
                {
                    tm = tm->upright;
                    upleft.x += ((downright.x - upleft.x) / 2);
                    downright.y -= ((downright.y - upleft.y) / 2);
                }
                else
                {
                    tm = tm->downright;
                    upleft.x += ((downright.x - upleft.x) / 2);
                    upleft.y += ((downright.y - upleft.y) / 2);
                }
            }
        }

        for (int i = 0; i < tm->data.size(); i++)
        {
            if (point == tm->data[i])
            {
                tm->data.erase(tm->data.begin() + i);
                return;
            }
        }
    }
    bool exist(OXY point)
    {
        if (point.x < 0 || point.x > ConsoleWidth || point.y < 0 || point.y > ConsoleHeight)
            return 0;

        node *tm = head;
        OXY upleft(0, 0), downright(ConsoleWidth, ConsoleHeight);
        while (tm->upleft != nullptr)
        {
            if (point.x < (upleft.x + downright.x) / 2)
            {
                if (point.y < (upleft.y + downright.y) / 2)
                {
                    tm = tm->upleft;
                    downright.x -= ((downright.x - upleft.x) / 2);
                    downright.y -= ((downright.y - upleft.y) / 2);
                }
                else
                {
                    tm = tm->downleft;
                    upleft.y += ((downright.y - upleft.y) / 2);
                    downright.x -= ((downright.x - upleft.x) / 2);
                }
            }
            else
            {
                if (point.y < (upleft.y + downright.y) / 2)
                {
                    tm = tm->upright;
                    upleft.x += ((downright.x - upleft.x) / 2);
                    downright.y -= ((downright.y - upleft.y) / 2);
                }
                else
                {
                    tm = tm->downright;
                    upleft.x += ((downright.x - upleft.x) / 2);
                    upleft.y += ((downright.y - upleft.y) / 2);
                }
            }
        }

        for (int i = 0; i < tm->data.size(); i++)
        {
            if (point == tm->data[i])
                return true;
        }
        return false;
    }
};

#endif