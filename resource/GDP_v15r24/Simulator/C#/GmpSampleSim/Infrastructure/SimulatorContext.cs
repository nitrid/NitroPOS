using GmpSampleSim.Models;

namespace GmpSampleSim.Infrastructure
{
    using System;
    using System.Data.Entity;
    using System.Data.Entity.ModelConfiguration.Conventions;
    using System.Linq;

    public class SimulatorContext : DbContext
    {
        public SimulatorContext()
            : base("name=SimulatorContext")
        {
            Database.SetInitializer<SimulatorContext>(new CreateDatabaseIfNotExists<SimulatorContext>());
        }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Conventions.Remove<PluralizingTableNameConvention>();
            base.OnModelCreating(modelBuilder);
        }

        public virtual DbSet<UniqueIdData> UniqueRecords { get; set; }
    }
}