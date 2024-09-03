using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.Win32;
using PWEB_2324.Data;
using PWEB_2324.Models;

namespace PWEB_2324.Controllers
{
    [Authorize("Admin")]
    public class LocadorController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly RoleManager<IdentityRole> _roleManager;
        private readonly UserManager<IdentityUser> _userManager;
        private readonly SignInManager<IdentityUser> _signInManager;

        public LocadorController(ApplicationDbContext context, RoleManager<IdentityRole> roleManager, UserManager<IdentityUser> userManager, SignInManager<IdentityUser> signInManager)
        {
            _context = context;
            _roleManager = roleManager;
            _userManager = userManager;
            _signInManager = signInManager;
        }

        public async Task<IActionResult> Index(string nomeLocador, bool? estadoSubscricao)
        {
            // Lógica para obter a lista de locadores com base nos filtros
            var locadores = await _context.Locadores.ToListAsync();
            // Aplicar os filtros
            if (!string.IsNullOrEmpty(nomeLocador))
            {
                locadores = locadores.Where(l => l.Nome.Contains(nomeLocador)).ToList();
            }
            if (estadoSubscricao.HasValue)
            {
                locadores = locadores.Where(l => l.Ativo == estadoSubscricao.Value).ToList();
            }

            return View(locadores);
        }


        public async Task<IActionResult> Details(int? id)
        {
            if (id == null || _context.Locadores == null)
            {
                return NotFound();
            }

            var loc = await _context.Locadores
                .Include(l => l.Imoveis)
                .FirstOrDefaultAsync(m => m.Id == id);

            if (loc == null)
            {
                return NotFound();
            }
            var imoveisDoLocador = await _context.Imoveis
            .Where(i => i.LocadorId == loc.Id)
            .ToListAsync();

            ViewBag.ImoveisDoLocador = imoveisDoLocador;

            if (loc.Imoveis == null || !loc.Imoveis.Any())
            {
                ViewBag.Message = "Locador sem Imóveis disponíveis.";
            }

            return View(loc);
        }


        public IActionResult Create()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Nome,Descricao,Avaliacao")] Locador locador)
        {

            ModelState.Remove(nameof(locador.Imoveis));

            if (ModelState.IsValid)
            {
                var user = new IdentityUser { UserName = locador.Nome };
                var result = await _userManager.CreateAsync(user, user.UserName + "2023!");
                locador.Ativo = true;
                if (result.Succeeded)
                {
                    _context.Add(locador);
                    await _context.SaveChangesAsync();

                    await _userManager.AddToRoleAsync(user, "Manager");
                    await _userManager.SetLockoutEnabledAsync(user, false);
                    var manager = new Manager { Id = user.Id, Nome = user.UserName, LocadorId = locador.Id };
                    _context.Add(manager);
                    await _context.SaveChangesAsync();

                    return RedirectToAction(nameof(Index));

                }
                else
                {
                    this.ModelState.AddModelError("Registro", "Necessário no minimo 1 letra maiuscula e uma letra minuscula");
                }
            }
            return View(locador);
        }

        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null || _context.Locadores == null)
            {
                return NotFound();
            }

            var loc = await _context.Locadores.FindAsync(id);
            if (loc == null)
            {
                return NotFound();
            }
            return View(loc);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Nome,Descricao,Avaliacao")] Locador locador)
        {
            if (id != locador.Id)
            {
                return NotFound();
            }
            ModelState.Remove(nameof(locador.Imoveis));
            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(locador);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!LocadorExists(locador.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(locador);
        }

        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null || _context.Locadores == null)
            {
                return NotFound();
            }

            var loc = await _context.Locadores
                .FirstOrDefaultAsync(m => m.Id == id);
            if (loc == null)
            {
                return NotFound();
            }

            return View(loc);
        }

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            if (_context.Locadores == null)
            {
                return Problem("Entity set 'ApplicationDbContext.Locadores'  is null.");
            }
            var loc = await _context.Locadores.FindAsync(id);
            if (loc != null)
            {


                var resultado = from c in _context.Alugados
                                where c.LocadorId == id && c.State == 1
                                select c;
                int count = resultado.Count();
                if (count == 0)
                {
                    var resultadoImoveis = _context.Imoveis.Where(c => c.LocadorId == id).ToList();

                    for (int i = 0; i < resultadoImoveis.Count(); i++)
                    {
                        var imovel = await _context.Imoveis.FindAsync(resultadoImoveis[i].Id);
                        _context.Imoveis.Remove(imovel);
                    }

                    _context.Locadores.Remove(loc);

                    var manager = _context.Managers.Where(c => c.LocadorId == id).ToList();
                    for (int i = 0; i < manager.Count(); i++)
                    {
                        var user = await _userManager.FindByIdAsync(manager[i].Id);
                        await _userManager.RemoveFromRoleAsync(user, "Manager");
                        await _userManager.DeleteAsync(user);

                    }
                    var func = _context.Funcionarios.Where(c => c.LocadorId == id).ToList();
                    for (int i = 0; i < func.Count(); i++)
                    {
                        var user = await _userManager.FindByIdAsync(func[i].Id);
                        await _userManager.RemoveFromRoleAsync(user, "Employee");
                        await _userManager.DeleteAsync(user);

                    }

                }
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool LocadorExists(int id)
        {
            return _context.Locadores.Any(e => e.Id == id);
        }

        public async Task<IActionResult> ToggleStatus(int? id)
        {
            if (id == null || _context.Locadores == null)
            {
                return NotFound();
            }

            var loc = await _context.Locadores.FindAsync(id);
            if (loc == null)
            {
                return NotFound();
            }

            loc.Ativo = !loc.Ativo; // Inverte o status
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }
    }
 }
