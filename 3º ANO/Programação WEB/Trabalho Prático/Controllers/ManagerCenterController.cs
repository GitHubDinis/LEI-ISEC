using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using PWEB_2324.Data;
using PWEB_2324.Models;
using PWEB_2324.ViewModels;
using System.Linq;

namespace PWEB_2324.Controllers
{
	[Authorize(Roles = "Manager")]
	public class ManagerCenterController : Controller
	{
		private readonly ApplicationDbContext _context;
		private readonly UserManager<IdentityUser> _userManager;
		private readonly RoleManager<IdentityRole> _roleManager;


		public ManagerCenterController(ApplicationDbContext context, UserManager<IdentityUser> userManager, RoleManager<IdentityRole> roleManager)
		{
			_context = context;
			_userManager = userManager;
			_roleManager = roleManager;
		}
		public async Task<IActionResult> Index()
		{
			var user = await _userManager.GetUserAsync(User);
			var manager = await _context.Managers.FindAsync(user.Id);


			return View(await _context.Funcionarios.
						Where(c => c.LocadorId == manager.LocadorId).OrderBy(c => c.Nome).ToListAsync());


        }
        public IActionResult Create()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Username,Password")] UserFormViewModel form)
        {
            ModelState.Remove(nameof(form.Id));
            var user = new IdentityUser { UserName = form.Username };
            var result = await _userManager.CreateAsync(user, form.Password);
           
            if (result.Succeeded)
			{
                var userLogged = await _userManager.GetUserAsync(User);
                var managerLogged = await _context.Managers.
                            Where(c => c.Id == userLogged.Id).ToListAsync();

                await _userManager.AddToRoleAsync(user, "Employee");
                await _userManager.SetLockoutEnabledAsync(user, false);
                var func = new Employee { Id = user.Id, Nome = user.UserName, LocadorId = managerLogged[0].LocadorId };
                _context.Add(func);
                await _context.SaveChangesAsync();

                return RedirectToAction(nameof(Index));
            }

            return View();
        }

        public IActionResult CreateManager()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> CreateManager([Bind("Username,Password")] UserFormViewModel form)
        {
            ModelState.Remove(nameof(form.Id));
            var user = new IdentityUser { UserName = form.Username };
            var result = await _userManager.CreateAsync(user, form.Password);

            if (result.Succeeded)
            {
                var userLogged = await _userManager.GetUserAsync(User);
                var managerLogged = await _context.Managers.
                            Where(c => c.Id == userLogged.Id).ToListAsync();

                await _userManager.AddToRoleAsync(user, "Manager");
                await _userManager.SetLockoutEnabledAsync(user, false);
                var func = new Manager { Id = user.Id, Nome = user.UserName, LocadorId = managerLogged[0].LocadorId };
                _context.Add(func);
                await _context.SaveChangesAsync();

                return RedirectToAction(nameof(Index));
            }

            return View();
        }

        public async Task<IActionResult> LockUnlock(string? id)
        {
            List<SelectListItem> Estados = new List<SelectListItem>();
            Estados.Add(new SelectListItem() { Value = "1", Text = "Bloquear" });
            Estados.Add(new SelectListItem() { Value = "2", Text = "Desbloquear" });

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
                    if (user.Estado == "1")
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

        public async Task<IActionResult> Delete(string? id)
        {
            if (id == null || _context.Imoveis == null)
            {
                return NotFound();
            }

            var func = await _context.Funcionarios
                .FirstOrDefaultAsync(m => m.Id == id);
            if (func == null)
            {
                return NotFound();
            }

            return View(func);
        }

        // POST: Imoveis/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(string id)
        {
            var user = await _userManager.FindByIdAsync(id);
            if (user == null)
            {
                return Problem("Entity set 'ApplicationDbContext.Imoveis'  is null.");
            }
            
            var result = await _userManager.DeleteAsync(user);
            if(result.Succeeded)
            {
                var func = await _context.Funcionarios
                .FirstOrDefaultAsync(m => m.Id == id);

                _context.Funcionarios.Remove(func);
                await _context.SaveChangesAsync();
            }

            
            return RedirectToAction(nameof(Index));
        }
    }
}
