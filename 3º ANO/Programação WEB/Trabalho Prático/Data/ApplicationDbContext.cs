using PWEB_2324.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace PWEB_2324.Data
{
    public class ApplicationDbContext : IdentityDbContext<IdentityUser>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        public DbSet<Imovel> Imoveis { get; set; }
        public DbSet<Categoria> Categorias { get; set; }
        public DbSet<Locador> Locadores { get; set; }
        public DbSet<Cliente> Clientes { get; set; }
        public DbSet<Employee> Funcionarios { get; set; }
        public DbSet<Alugado> Alugados { get; set; }
        public DbSet<Manager> Managers { get; set; }
    }
}