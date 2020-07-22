using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace FirstLibrary
{
    public static class Protector
    {
        private static readonly byte[] salt = Encoding.Unicode.GetBytes("5TOPCOOLSALT5");
        private static readonly int iterations = 2000;

        public static string Encrypt( string plainText, string password ) {
            byte[] encryptedBytes;
            byte[] plainBytes = Encoding.Unicode.GetBytes(plainText);

            var aes = Aes.Create();
            var pbkdf2 = new Rfc2898DeriveBytes(password, salt, iterations);

            aes.Key = pbkdf2.GetBytes(32);
            aes.IV = pbkdf2.GetBytes(16);

            using ( var ms = new MemoryStream( ) ) {
                using ( var cs = new CryptoStream(ms, aes.CreateEncryptor( ), CryptoStreamMode.Write) ) {
                    cs.Write(plainBytes, 0, plainBytes.Length);
                }
                encryptedBytes = ms.ToArray( );
            }

            return Convert.ToBase64String(encryptedBytes);
        }

        public static string Dectypt( string encryptedText, string password ) {
            byte[] plainBytes;
            byte[] encryptedBytes = Convert.FromBase64String(encryptedText);

            var aes = Aes.Create();
            var pbkdf2 = new Rfc2898DeriveBytes(password, salt, iterations);

            aes.Key = pbkdf2.GetBytes(32);
            aes.IV = pbkdf2.GetBytes(16);

            using ( var ms = new MemoryStream( ) ) {
                using ( var cs = new CryptoStream(ms, aes.CreateDecryptor( ), CryptoStreamMode.Write) ) {
                    cs.Write(encryptedBytes, 0, encryptedBytes.Length);
                }
                plainBytes = ms.ToArray( );
            }

            return Encoding.Unicode.GetString(plainBytes);
        }
    }
}