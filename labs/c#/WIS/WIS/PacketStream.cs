using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace WIS
{
	public class PacketStream
	{

		private MemoryStream FStream;

		private BinaryReader FReader;

		private BinaryWriter FWriter;



		public PacketStream()
		{

			FStream = new MemoryStream();

			FReader = new BinaryReader(FStream, Encoding.Unicode);

			FWriter = new BinaryWriter(FStream, Encoding.Unicode);

		}


		public PacketStream(byte[] data, int offset, int bytes)
		{

			FStream = new MemoryStream(data, offset, bytes, true);

			FReader = new BinaryReader(FStream);

			FWriter = new BinaryWriter(FStream);

		}


		public void Seek(int offset)
		{

			FStream.Seek(offset, SeekOrigin.Begin);

		}


		public UInt32 GetLength()
		{

			return (UInt32)FStream.Length;

		}


		public byte[] GetBytes()
		{

			return FStream.GetBuffer();

		}


		public void WriteByte(byte data)
		{

			FWriter.Write(data);

		}


		public void WriteUInt16(UInt16 data)
		{

			FWriter.Write(data);

		}


		public void WriteUInt32(UInt32 data)
		{

			FWriter.Write(data);

		}


		public void WriteUInt64(UInt64 data)
		{

			FWriter.Write(data);

		}


		public void WriteString(string data)
		{

			FWriter.Write((UInt16)data.Length);


			byte[] str = UnicodeEncoding.Unicode.GetBytes(data);

			FWriter.Write(str);

		}

		public void WriteFixedString(string data, UInt16 fixedCount)
		{

			FWriter.Write((UInt16)data.Length);

			
			byte[] str = UnicodeEncoding.Unicode.GetBytes(data);

			FWriter.Write(str);


			for (int i = 0; i < (fixedCount - data.Length); ++i)
			{

				FWriter.Write((UInt16)0);

			}

		}



		public void WriteString_MD5(string data)
		{

			MD5 md5 = MD5.Create();

			byte[] hash = md5.ComputeHash(Encoding.Default.GetBytes(data));

			FWriter.Write(hash);

		}


		public void WriteFloat(float data)
		{

			FWriter.Write(data);

		}


		public void WriteDouble(double data)
		{

			FWriter.Write(data);

		}


		public byte ReadByte()
		{

			return FReader.ReadByte();

		}


		public UInt16 ReadUInt16()
		{

			return FReader.ReadUInt16();

		}


		public UInt32 ReadUInt32()
		{

			return FReader.ReadUInt32();

		}


		public UInt64 ReadUInt64()
		{

			return FReader.ReadUInt64();

		}


		public string ReadString()
		{

			UInt16 count = FReader.ReadUInt16();

			byte[] str = FReader.ReadBytes(count * 2);


			return UnicodeEncoding.Unicode.GetString(str);

		}

		public string ReadFixedString(UInt16 fixedCount)
		{

			UInt16 count = FReader.ReadUInt16();

			byte[] str = FReader.ReadBytes(count * 2);

			FReader.ReadBytes((fixedCount - count) * 2);


			return UnicodeEncoding.Unicode.GetString(str);

		}

		public float ReadFloat()
		{

			return FReader.ReadSingle();

		}
		public double ReadDouble()
		{

			return FReader.ReadDouble();

		}

	}
}
