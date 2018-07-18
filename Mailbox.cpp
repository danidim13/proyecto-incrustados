/*
 * Mailbox.cpp
 *
 *  Created on: May 1, 2018
 *      Author: eortiz
 */

#include <Mailbox.hpp>

Mailbox* Mailbox::MailObj = nullptr;

extern "C"
{
    Mailbox* Mailbox::getMailbox()
    {
        if(MailObj == nullptr)
        {
            MailObj = new Mailbox();
        }

        return MailObj;
    }

    st_Message Mailbox::getMessage(uint8_t i_u8MailboxID)
    {
        st_Message l_stMessage;
        l_stMessage.bMessageValid = false;

        l_stMessage = m_stMessageQueue[i_u8MailboxID];
        m_stMessageQueue[i_u8MailboxID].bMessageValid = false;


        /*if (m_stMessageQueue[i_u8MailboxID].num_elem() > 0) {
            l_stMessage = m_stMessageQueue[i_u8MailboxID].pop_front();
        }*/

        return(l_stMessage);
    }

    bool Mailbox::sendMessage(st_Message i_stMessage)
    {

        if(m_stMessageQueue[i_stMessage.u8DestinationID].bMessageValid == false)
        {
            m_stMessageQueue[i_stMessage.u8DestinationID] = i_stMessage;
            return(true);
        }
        /*if (m_stMessageQueue[i_stMessage.u8DestinationID].full() == false){
            m_stMessageQueue[i_stMessage.u8DestinationID].push_back(i_stMessage);
            return(true);
        }*/
        else
        {
            return(false);
        }
    }
}


