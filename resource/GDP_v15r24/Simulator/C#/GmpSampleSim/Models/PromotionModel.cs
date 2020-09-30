using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel.DataAnnotations;
namespace GmpSampleSim.Models
{
    public enum PromotionType { DISCOUNT=1, INCREASE };

    public class PromotionModel
    {
        private static PromotionModel _instance = null;
        private PromotionModel() { }

        public static PromotionModel Instance {
            get {
                if (_instance == null)
                {
                    _instance = new PromotionModel();
                }
                return _instance;
            }
        }

        public PromotionType Type { get; set; }

        public UInt32 Amount { get; set; }

        [StringLength(32)]
        public string Message { get; set; }

        public void Clear()
        {
            Amount = 0;
            Message = "";
        }
    }
}
