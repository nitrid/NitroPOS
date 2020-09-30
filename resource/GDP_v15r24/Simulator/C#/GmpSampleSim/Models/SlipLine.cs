using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GmpSampleSim.Models
{
    class SlipLine
    {
        public byte Format_T { get; set; } // for ticket type
        public byte Format_F { get; set; } // for font size
        public byte Format_P { get; set; } // for line property
        public string Line { get; set; }
    }
}
