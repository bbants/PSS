#ifndef _CONSOLEMESSAGE_H
#define _CONSOLEMESSAGE_H

#include "MessageDispose.h"
#include "XmlConfig.h"

class CConsoleMessage
{
public:
    CConsoleMessage();
    ~CConsoleMessage();

    int Dispose(ACE_Message_Block* pmb, IBuffPacket* pBuffPacket, uint8& u1OutputType);     //Ҫ�����������ֽ���, pBuffPacketΪ����Ҫ���͸��ͻ��˵�����
    int ParsePlugInCommand(const char* pCommand, IBuffPacket* pBuffPacket);                 //ִ������

    int Init();                                                                             //��ʼ���������

    //��ʼ������
    bool SetConsoleKey(vector<xmlConsoleKeys::_ConsoleKey> vecConsoleKeyList);       //������֤������keyֵ

private:
    int  ParseCommand_Plugin(const char* pCommand, IBuffPacket* pBuffPacket, uint8& u1OutputType);            //ִ������(����ڲ�����)
    int  ParseCommand(const char* pCommand, IBuffPacket* pBuffPacket, uint8& u1OutputType);                   //ִ������
    int  DoCommand(_CommandInfo& CommandInfo, IBuffPacket* pCurrBuffPacket, IBuffPacket* pReturnBuffPacket);  //������������
    bool GetCommandInfo(const char* pCommand, _CommandInfo& CommandInfo, bool blCheck = true);                //�������и��Ӧ���е����ݸ�ʽ
    bool CheckConsoleKey(const char* pKey);                                                                   //��֤key

    vector<xmlConsoleKeys::_ConsoleKey> m_vecConsolekeyList;
    CConsolePromissions m_objConsolePromissions;

    //����ͳһ�ĺ���ָ��ģ��
    typedef void(*DoMessage_Logic)(_CommandInfo& CommandInfo, IBuffPacket* pBuffPacket, uint16& u2ReturnCommandID);
    typedef ACE_Hash_Map<string, DoMessage_Logic> mapMessageList;
    mapMessageList      m_objHashMessageLogicList;             //��������Hash�б�
};

typedef ACE_Singleton<CConsoleMessage, ACE_Null_Mutex> App_ConsoleManager;
#endif