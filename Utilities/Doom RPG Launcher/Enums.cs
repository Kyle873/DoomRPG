using System;

namespace DoomRPG
{
    public enum Difficulty
    {
        Easy,
        Normal,
        Hard,
        Nightmare,
        Hell,
        Armegeddon
    }

    public enum MultiplayerMode
    {
        Hosting,
        Joining
    }

    public enum ServerType
    {
        PeerToPeer,
        PacketServer
    }
}
