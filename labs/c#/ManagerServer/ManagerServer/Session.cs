using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ManagerServer
{
    class Packet
    {
    };
    class Session
    {

        private delegate void Handler_RegisterServer(Packet packet);

        public bool Initialize()
        {
            return true;
        }

        public void Release()
        {
        }

        
    }
}
