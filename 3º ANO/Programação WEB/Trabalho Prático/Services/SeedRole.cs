using Microsoft.AspNetCore.Identity;
using PWEB_2324.Data;
using PWEB_2324.Models;

namespace PWEB_2324.Services
{
    public class SeedRole : ISeedRole
    {
        private readonly UserManager<IdentityUser> _userManager;
        private readonly RoleManager<IdentityRole> _roleManager;
        private readonly ApplicationDbContext _context;

        public SeedRole(UserManager<IdentityUser> userManager, RoleManager<IdentityRole> roleManager, ApplicationDbContext context)
        {
            _userManager = userManager;
            _roleManager = roleManager;
            _context = context;
        }

        public void SeedRoles()
        {
            if (!_roleManager.RoleExistsAsync("Client").Result)
            {
                IdentityRole role = new IdentityRole();
                role.Name = "Client";
                role.NormalizedName = "CLIENT";
                IdentityResult roleResult = _roleManager.CreateAsync(role).Result;
            }
            if (!_roleManager.RoleExistsAsync("Employee").Result)
            {
                IdentityRole role = new IdentityRole();
                role.Name = "Employee";
                role.NormalizedName = "EMPLOYEE";
                IdentityResult roleResult = _roleManager.CreateAsync(role).Result;
            }
            if (!_roleManager.RoleExistsAsync("Manager").Result)
            {
                IdentityRole role = new IdentityRole();
                role.Name = "Manager";
                role.NormalizedName = "MANAGER";
                IdentityResult roleResult = _roleManager.CreateAsync(role).Result;
            }
            if (!_roleManager.RoleExistsAsync("Admin").Result)
            {
                IdentityRole role = new IdentityRole();
                role.Name = "Admin";
                role.NormalizedName = "ADMIN";
                IdentityResult roleResult = _roleManager.CreateAsync(role).Result;
            }
        }

        public void SeedUsers()
        {
            if(_userManager.FindByEmailAsync("FuncRemax").Result == null)
            {
                IdentityUser user = new IdentityUser();
                user.UserName = "FuncRemax";
                user.Email = "FuncRemax";
                user.NormalizedEmail = "FUNCREMAX";
                user.NormalizedUserName = "FUNCREMAX";
                user.EmailConfirmed = true;
                user.LockoutEnabled = false;
                user.SecurityStamp = Guid.NewGuid().ToString();

                IdentityResult result = _userManager.CreateAsync(user, "Remax2023!").Result;
                if (result.Succeeded)
                {
                    _userManager.AddToRoleAsync(user, "Employee").Wait();
					_userManager.SetLockoutEnabledAsync(user, false).Wait();

                    var func = new Employee { Id = user.Id, Nome = user.UserName, LocadorId = 1 };
                    _context.Add(func);
                    _context.SaveChangesAsync().Wait();
                }
            }
            if (_userManager.FindByEmailAsync("FuncEximios").Result == null)
            {
                IdentityUser user = new IdentityUser();
                user.UserName = "FuncEximios";
                user.Email = "FuncEximios";
                user.NormalizedEmail = "FUNCEXIMIOS";
                user.NormalizedUserName = "FUNCEXIMIOS";
                user.EmailConfirmed = true;
                user.LockoutEnabled = false;
                user.SecurityStamp = Guid.NewGuid().ToString();

                IdentityResult result = _userManager.CreateAsync(user, "Eximios2023!").Result;
                if (result.Succeeded)
                {
                    _userManager.AddToRoleAsync(user, "Employee").Wait();
					_userManager.SetLockoutEnabledAsync(user, false).Wait();
					//Apenas para testes
					var func = new Employee { Id = user.Id, Nome = user.UserName, LocadorId = 2 };
                    _context.Add(func);
                    _context.SaveChangesAsync().Wait();
                }
            }
            if (_userManager.FindByEmailAsync("Remax").Result == null)
            {
                IdentityUser user = new IdentityUser();
                user.UserName = "Remax";
                user.Email = "Remax";
                user.NormalizedEmail = "REMAX";
                user.NormalizedUserName = "REMAX";
                user.EmailConfirmed = true;
                user.LockoutEnabled = false;
                user.SecurityStamp = Guid.NewGuid().ToString();

                IdentityResult result = _userManager.CreateAsync(user, "Remax2023!").Result;
                if (result.Succeeded)
                {
                    _userManager.AddToRoleAsync(user, "Manager").Wait();
					_userManager.SetLockoutEnabledAsync(user, false).Wait();
                    var manager = new Manager { Id = user.Id, Nome = user.UserName, LocadorId = 1 };
                    _context.Add(manager);
                    _context.SaveChangesAsync().Wait();
                }
            }
            if (_userManager.FindByEmailAsync("Eximios").Result == null)
            {
                IdentityUser user = new IdentityUser();
                user.UserName = "Eximios";
                user.Email = "Eximios";
                user.NormalizedEmail = "EXIMIOS";
                user.NormalizedUserName = "EXIMIOS";
                user.EmailConfirmed = true;
                user.LockoutEnabled = false;
                user.SecurityStamp = Guid.NewGuid().ToString();

                IdentityResult result = _userManager.CreateAsync(user, "Eximios2023!").Result;
                if (result.Succeeded)
                {
                    _userManager.AddToRoleAsync(user, "Manager").Wait();
                    _userManager.SetLockoutEnabledAsync(user, false).Wait();

                    var manager = new Manager { Id = user.Id, Nome = user.UserName, LocadorId = 2 };
                    _context.Add(manager);
                    _context.SaveChangesAsync().Wait();
                }
            }
            if (_userManager.FindByEmailAsync("admin").Result == null)
            {
                IdentityUser user = new IdentityUser();
                user.UserName = "admin";
                user.Email = "admin";
                user.NormalizedEmail = "ADMIN";
                user.NormalizedUserName = "ADMIN";
                user.EmailConfirmed = true;
                user.LockoutEnabled = false;
                user.SecurityStamp = Guid.NewGuid().ToString();

                IdentityResult result = _userManager.CreateAsync(user, "Admin2023!").Result;
                if (result.Succeeded)
                {
                    _userManager.AddToRoleAsync(user, "Admin").Wait();
					_userManager.SetLockoutEnabledAsync(user, false).Wait();
				}
            }
        }
    }
}
