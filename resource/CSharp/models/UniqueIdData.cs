using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel.DataAnnotations;

namespace GmpSampleSim.Models
{
    public class UniqueIdData
    {
        [Key]
        public int Id { get; set; }
        public string UniqueId { get; set; }
        public DateTime RecordTime { get; set; }
    }
}
