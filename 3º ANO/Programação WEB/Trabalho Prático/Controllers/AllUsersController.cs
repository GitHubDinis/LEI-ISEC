using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using PWEB_2324.Data;
using PWEB_2324.Models;
using PWEB_2324.ViewModels;

namespace PWEB_2324.Controllers
{
    [Authorize(Roles = "Admin")]
    public class AllUsersController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;
        private readonly RoleManager<IdentityRole> _roleManager;
        private List<UsersViewModel> GetFilteredUsers(string usernameFilter, string roleFilter, string orderBy)
        {
            var usersQuery = _userManager.Users.Select(c => new UsersViewModel()
            {
                Id = c.Id,
                Username = c.UserName,
                Email = c.Email,
                Role = string.Join(",", _userManager.GetRolesAsync(c).Result.ToArray())
            });

            if (!string.IsNullOrEmpty(usernameFilter))
            {
                usersQuery = usersQuery.Where(u => u.Username.Contains(usernameFilter));
            }
            if (!string.IsNullOrEmpty(roleFilter))
            {
                usersQuery = usersQuery.Where(u => u.Role.Contains(roleFilter));
            }
            if (!string.IsNullOrEmpty(orderBy))
            {
                if (orderBy == "UsernameAsc")
                {
                    usersQuery = usersQuery.OrderBy(u => u.Username);
                }
                else if (orderBy == "UsernameDesc")
                {
                    usersQuery = usersQuery.OrderByDescending(u => u.Username);
                }
                else if (orderBy == "RoleAsc")
                {
                    usersQuery = usersQuery.OrderBy(u => u.Role);
                }
                else if (orderBy == "RoleDesc")
                {
                    usersQuery = usersQuery.OrderByDescending(u => u.Role);
                }
            }
            return usersQuery.ToList();
        }

        public AllUsersController(ApplicationDbContext context, UserManager<IdentityUser> userManager, RoleManager<IdentityRole> roleManager)
        {
            _context = context;
            _userManager = userManager;
            _roleManager = roleManager;
        }
        public IActionResult Index(string usernameFilter, string roleFilter, string orderBy)
        {
            var users = GetFilteredUsers(usernameFilter, roleFilter, orderBy);
            return View(users);
        }


        public async Task<IActionResult> Edit(string? id)
        {
            ViewData["ListaDeRoles"] = new SelectList(_roleManager.Roles.ToList(), "Name");
            var user = await _userManager.FindByIdAsync(id);

            if (id == null || user == null)
            {
                return NotFound();
            }
            var userView = new UsersViewModel()
            {
                Id= user.Id,
                Username = user.UserName,
                Email = user.Email,
                Role = string.Join(",", _userManager.GetRolesAsync(user).Result.ToArray())
            };

            return View(userView);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(string id, [Bind("Id,Username,Email,Role")] UsersViewModel user)
        {
            if (id != user.Id)
            {
                return NotFound();
            }
            ModelState.Remove(nameof(user.Email));
            ModelState.Remove(nameof(user.Estado));
            if (ModelState.IsValid)
            {
                try
                {
                    var userFind = await _userManager.FindByIdAsync(id);
                    var role = string.Join(",", _userManager.GetRolesAsync(userFind).Result.ToArray());
                    if(role != "")
                    {
                        var res = await _userManager.RemoveFromRoleAsync(userFind, role);
                    }
                    _userManager.AddToRoleAsync(userFind, user.Role).Wait();
                }
                catch (DbUpdateConcurrencyException)
                {
                   
                }
                return RedirectToAction(nameof(Index));
            }

            return View(user);
        }
        public async Task<IActionResult> LockUnlock(string? id)
        {
            List<SelectListItem> Estados = new List<SelectListItem>();
            Estados.Add(new SelectListItem() { Value = "1", Text = "Bloquear"  });
            Estados.Add(new SelectListItem() { Value = "2", Text = "Desbloquear"  });

            ViewBag.ListaDeEstados = new SelectList(Estados, "Value", "Text");

            var user = await _userManager.FindByIdAsync(id);

            if (id == null || user == null)
            {
                return NotFound();
            }
            var userView = new UsersViewModel()
            {
                Id = user.Id,
                Username = user.UserName,
                Email = user.Email,
                Role = string.Join(",", _userManager.GetRolesAsync(user).Result.ToArray())
            };

            return View(userView);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> LockUnlock(string id, [Bind("Id,Username,Email,Role,Estado")] UsersViewModel user)
        {
            if (id != user.Id)
            {
                return NotFound();
            }
            ModelState.Remove(nameof(user.Email));
            if (ModelState.IsValid)
            {
                try
                {
                    var userFind = await _userManager.FindByIdAsync(id);
                    if(user.Estado == "1")
                    {
                        await _userManager.SetLockoutEnabledAsync(userFind, true);
                    }
                    else
                    {
                        await _userManager.SetLockoutEnabledAsync(userFind, false);
                    }
                }
                catch (DbUpdateConcurrencyException)
                {

                }
                return RedirectToAction(nameof(Index));
            }

            return View(user);
        }
    }
}
