using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data.Common;
using System.Data.SqlClient;
using System.Security;
using System.Security.Cryptography;
using System.Data;
using System.Configuration;
namespace ElementiaWS
{
	/// <summary>
	/// Summary description for Service1
	/// </summary>
	[WebService(Namespace = "http://yooluck.com/")]
	[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
	[System.ComponentModel.ToolboxItem(false)]
	// To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
	// [System.Web.Script.Services.ScriptService]
	public class RookieCard : System.Web.Services.WebService
	{
		enum RookieCardExchangeRetValue
		{

			ret_ok = 0,

			ret_expired,

			ret_already_used,

			ret_invalid_code,

			ret_invalid_region,

			ret_invalid_partner,

		};
		

		[WebMethod]
		public byte UseCard(string code, int regionId, int partnerId, out UInt32 itemTemplate)
		{

			itemTemplate = 0xffffffff;

			using (SqlConnection con = new SqlConnection())
			{

				con.ConnectionString = System.Configuration.ConfigurationSettings.AppSettings["db_con"];


				string cmdStr = string.Format("SELECT * FROM rookie_cards where card_code = '{0}'", code);

				con.Open();

				SqlCommand cmd = new SqlCommand(cmdStr, con);

				SqlDataReader reader = cmd.ExecuteReader();

				
				
				if(false == reader.Read())
				{

					return (byte)RookieCardExchangeRetValue.ret_invalid_code;

				}


				if ((bool)reader["used"])
				{

					return (byte)RookieCardExchangeRetValue.ret_already_used;

				}


				if((bool)reader["expired"])
				{

					return (byte)RookieCardExchangeRetValue.ret_expired;

				}


				int rid = (int)reader["region_id"];
 
				int pid = (int)reader["partner_id"];

				if (rid != -1 && regionId != -1)
				{

					if (rid != regionId)
					{

						return (byte)RookieCardExchangeRetValue.ret_invalid_region;

					}

				}


				if (pid != -1 && partnerId != -1)
				{

					if (pid != partnerId)
					{

						return (byte)RookieCardExchangeRetValue.ret_invalid_partner;

					}

				}
				

				DateTime expireDate = (DateTime)reader["expire_date"];

				if (expireDate.CompareTo(DateTime.Now) < 0)
				{

					reader.Close();

					
					cmd.CommandText = string.Format("Update rookie_cards set expired = 1 where card_code = '{0}'", code);
					
					cmd.ExecuteNonQuery();
					

					return (byte)RookieCardExchangeRetValue.ret_expired;

				}

				int templateId = (int)reader["item_template"];

				itemTemplate = (UInt32)templateId;

				reader.Close();


				cmd.CommandText = string.Format("update rookie_cards set used = 1, used_date = GetDate() where card_code = '{0}'", code);
	
				cmd.ExecuteNonQuery();

			}

			return (byte)RookieCardExchangeRetValue.ret_ok;

		}

		[WebMethod]
		public string GenerateCard(string str, string md5Str, int generation, int regionId, int partnerId, DateTime expire, UInt32 packId)
		{
			if (false == Auth(str, md5Str))
			{
				throw new ArgumentException("认证字符串无效");
			}

			return _GenerateCard(generation, regionId, partnerId, expire, packId);
		}

		[WebMethod]
		public string GenerateCard_debug(int generation, int regionId, int partnerId, DateTime expire, UInt32 packId)
		{
			
			return _GenerateCard(generation, regionId, partnerId, expire, packId);
		}



		[WebMethod]
		public List<string> GenerateCards(string str, string md5Str, int count, int generation, int regionId, int partnerId, DateTime expire, UInt32 packId)
		{
			if (false == Auth(str, md5Str))
			{
				throw new ArgumentException("认证字符串无效");
			}

			return _GenerateCards(count, generation, regionId, partnerId, expire, packId);

		}

		[WebMethod]
		public List<string> GenerateCards_debug(int count, int generation, int regionId, int partnerId, DateTime expire, UInt32 packId)
		{
			

			return _GenerateCards(count, generation, regionId, partnerId, expire, packId);

		}

		private string GenCard(int generation, string pre, int partner_id)
		{

			return string.Format("xs{0:d2}{1:d2}{2}", generation.ToString("00"), partner_id, GenString(6));

		}


		private string GenString(int count)
		{
			byte[] randomNumber = new byte[count];

			RNGCryptoServiceProvider Gen = new RNGCryptoServiceProvider();

			Gen.GetBytes(randomNumber);


			string str_rand = "";
			
			for (int i = 0; i < count; ++i)
			{
				byte num = randomNumber[i];

				num = (byte)((float)num / 255.0f * 99.0f);

				str_rand += num.ToString("00");

			}


			return str_rand;

		}

		private bool InsertIntoDB(SqlCommand cmd, List<string> cards, int server_id, int partner_id, DateTime expire, UInt32 packId)
		{

			foreach(string card in cards)
			{

				cmd.CommandText = string.Format("insert into rookie_cards(card_code, item_template, region_id, gen_date, partner_id, expire_date) values('{0}',{1},{2},{3},{4},'{5}')",
																						card, packId, server_id, "GetDate()", partner_id, expire);

				cmd.ExecuteNonQuery();

			}

			return true;

		}

		private bool CardExists(SqlCommand cmd, string card)
		{

			cmd.CommandText = string.Format("select * from rookie_cards where card_code = '{0}'", card);

			SqlDataReader reader = cmd.ExecuteReader();

			bool existed = reader.Read();

			reader.Close();

			return existed;

		}

		private bool Auth(string str, string MD5str)
		{
			string key = ConfigurationSettings.AppSettings["auth_key"];


			string md5str = System.Web.Security.FormsAuthentication.HashPasswordForStoringInConfigFile(str + key , "MD5");

			if (md5str.ToLower() != MD5str.ToLower())
			{
				return false;
			}

			return true;
		}

		
		private string _GenerateCard(int generation, int regionId, int partnerId, DateTime expire, UInt32 packId)
		{
		
			using (SqlConnection con = new SqlConnection())
			{

				con.ConnectionString = System.Configuration.ConfigurationSettings.AppSettings["db_con"];

				con.Open();

				SqlCommand cmd = new SqlCommand();

				cmd.Connection = con;

				string card;
				do
				{
					card = GenCard(generation, "XS", partnerId);


				} while (CardExists(cmd, card) == true);

				List<string> cards = new List<string>();

				cards.Add(card);

				InsertIntoDB(cmd, cards, regionId, partnerId, expire, packId);


				return card;
			}

		}

		[WebMethod]
		public List<string> _GenerateCards(int count, int generation, int regionId, int partnerId, DateTime expire, UInt32 packId)
		{
			using (SqlConnection con = new SqlConnection())
			{

				con.ConnectionString = System.Configuration.ConfigurationSettings.AppSettings["db_con"];

				con.Open();

				SqlCommand cmd = new SqlCommand();

				cmd.Connection = con;

				List<string> cards = new List<string>();

				for (int i = 0; i < count; ++i)
				{

					string card;

					do
					{
						card = GenCard(generation, "XS", partnerId);

					} while (CardExists(cmd, card) == true);

					cards.Add(card);

				}


				InsertIntoDB(cmd, cards, regionId, partnerId, expire, packId);

				return cards;
			}

		}
	}
}


