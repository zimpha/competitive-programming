using System;
using System.Diagnostics;
using System.Linq;
using System.IO;
using System.Collections.Generic;

namespace euler {
    class Problem59 {


        public static void Main(string[] args) {
            new Problem59().FrequencyAnalysis();
        }

        public void FrequencyAnalysis() {
            Stopwatch clock = Stopwatch.StartNew();

            string filename = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory) + "\\input.txt";
            const int keyLength = 3;

            int[] message = File.ReadAllText(filename).Split(',').Select(int.Parse).ToArray();
            int[] key = Analysis(message, keyLength);
            int[] decryptedMessage = EncryptLinq(message, key);            
            int result = decryptedMessage.Sum();

            
            clock.Stop();
            Console.WriteLine("The sum of the decrypted message is {0}", result);
            Console.WriteLine("Solution took {0} ms", clock.ElapsedMilliseconds);

            for (int i = 0; i < decryptedMessage.Length; i++) {
                Console.Write(Convert.ToChar(decryptedMessage[i]));
            }
        }

        private int[] Encrypt(int[] message, int[] key) {

            int[] encryptedMessage = new int[message.Length];
            
            for (int i = 0; i < message.Length; i++) {
                encryptedMessage[i] = message[i] ^ key[i%key.Length];                
            }

            return encryptedMessage;
        }


        private int[] EncryptLinq(int[] message, int[] key) {

            IEnumerable<int> repeatedKey = Enumerable.Range(0, message.Length).Select(x => key[x % key.Length]);
            return message.Zip(repeatedKey, (x, y) => (x ^ y)).ToArray();
        }

        private int[] Analysis(int[] message, int keyLength) {     
            int maxsize = 0;
            for (int i = 0; i < message.Length; i++) {
                if (message[i] > maxsize) maxsize = message[i];
            }

            int[,] aMessage = new int[keyLength, maxsize+1];
            int[] key = new int[keyLength];
                        
            for (int i = 0; i < message.Length; i++) {
                int j = i % keyLength;
                aMessage[j, message[i]]++;
                if (aMessage[j, message[i]] > aMessage[j, key[j]]) key[j] = message[i];
            }
            
            int spaceAscii = 32;
            for (int i = 0; i < keyLength; i++) {
                key[i] = key[i] ^ spaceAscii;
            }

            return key;
        }       

    }
}
