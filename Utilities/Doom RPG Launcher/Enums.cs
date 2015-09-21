using System;

namespace DoomRPG
{
    public enum IWAD
    {
        Doom1,
        Doom2,
        Plutonia,
        TNT
    }

    public enum Difficulty
    {
        Easy,
        Normal,
        Hard,
        Nightmare,
        Hell,
        Armegeddon
    }

    public enum DRLAClass
    {
        Marine,
        Scout,
        Technician,
        Renegade,
        Demolitionist
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
