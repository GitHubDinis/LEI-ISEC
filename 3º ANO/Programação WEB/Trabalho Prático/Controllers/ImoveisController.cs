using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
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
    [Authorize(Roles = "Employee,Manager")]
    public class ImoveisController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;

        public ImoveisController(ApplicationDbContext context, UserManager<IdentityUser> userManager)
        {
            _context = context;
            _userManager = userManager;
        }

        // GET: Imoveis
        public async Task<IActionResult> Index(bool? disponivel)
        {
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            var user = await _userManager.GetUserAsync(User);
            // bool test = _userManager.IsInRoleAsync(user, "Employee");
            if(user != null)
            {
                if (await _userManager.IsInRoleAsync(user, "Employee"))
                {
                    var f = await _context.Funcionarios.FindAsync(user.Id);
                    if (disponivel != null)
                    {
                        if (disponivel == true)
                            ViewData["Title"] = "Lista de Imoveis Activos";
                        else
                            ViewData["Title"] = "Lista de Imoveis Inactivos";

                        return View(await _context.Imoveis.Include("categoria").
                            Where(c => c.Available == disponivel && c.LocadorId == f.LocadorId).OrderBy(c => c.Title).ToListAsync()
                            );
                    }
                    else
                    {
                        ViewData["Title"] = "Lista de Imoveis";
                        return View(await _context.Imoveis.Include("categoria").Where(c => c.LocadorId == f.LocadorId).OrderBy(c => c.Title).ToListAsync());
                    }
                }
                else if (await _userManager.IsInRoleAsync(user, "Manager"))
                {
                    var manager = await _context.Managers.FindAsync(user.Id);
                    if (disponivel != null)
                    {
                        if (disponivel == true)
                            ViewData["Title"] = "Lista de Imoveis Activos";
                        else
                            ViewData["Title"] = "Lista de Imoveis Inactivos";

                        return View(await _context.Imoveis.Include("categoria").
                            Where(c => c.Available == disponivel && c.LocadorId == manager.LocadorId).OrderBy(c => c.Title).ToListAsync()
                            );
                    }
                    else
                    {
                        ViewData["Title"] = "Lista de Imoveis";
                        return View(await _context.Imoveis.Include("categoria").Where(c => c.LocadorId == manager.LocadorId).OrderBy(c => c.Title).ToListAsync());
                    }
                }
                else
                {
                    if (disponivel != null)
                    {
                        if (disponivel == true)
                            ViewData["Title"] = "Lista de Imoveis Activos";
                        else
                            ViewData["Title"] = "Lista de Imoveis Inactivos";

                        return View(await _context.Imoveis.Include("categoria").
                            Where(c => c.Available == disponivel).OrderBy(c => c.Title).ToListAsync()
                            );
                    }
                    else
                    {
                        ViewData["Title"] = "Lista de Imoveis";
                        return View(await _context.Imoveis.Include("categoria").OrderBy(c => c.Title).ToListAsync());
                    }
                }
            } 
            else {
                if (disponivel != null)
                {
                    if (disponivel == true)
                        ViewData["Title"] = "Lista de Imoveis Activos";
                    else
                        ViewData["Title"] = "Lista de Imoveis Inactivos";

                    return View(await _context.Imoveis.Include("categoria").
                        Where(c => c.Available == disponivel).OrderBy(c => c.Title).ToListAsync()
                        );
                }
                else
                {
                    ViewData["Title"] = "Lista de Imoveis";
                    return View(await _context.Imoveis.Include("categoria").OrderBy(c => c.Title).ToListAsync());
                }
            }
        }

        [HttpPost]
        public async Task<IActionResult> Index(string TextoAPesquisar, int CategoriaId)
        {
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            var user = await _userManager.GetUserAsync(User);

            if (user != null)
            {
                if (await _userManager.IsInRoleAsync(user, "Employee"))
                {
                    var f = await _context.Funcionarios.FindAsync(user.Id);
                    if (string.IsNullOrWhiteSpace(TextoAPesquisar))
                    {
                        return View(_context.Imoveis.Where(c => c.CategoriaId == CategoriaId && c.LocadorId == f.LocadorId));
                    } 
                    else
                    {
                        var resultado = from c in _context.Imoveis
                                        where c.Title.Contains(TextoAPesquisar) && c.CategoriaId == CategoriaId && c.LocadorId == f.LocadorId
                                        select c;
                        return View(resultado);
                    }
                }
                else if (await _userManager.IsInRoleAsync(user, "Manager"))
                {
                    var manager = await _context.Managers.FindAsync(user.Id);
                    if (string.IsNullOrWhiteSpace(TextoAPesquisar))
                    {
                        return View(_context.Imoveis.Where(c => c.CategoriaId == CategoriaId && c.LocadorId == manager.LocadorId));
                    }
                    else
                    {
                        var resultado = from c in _context.Imoveis
                                        where c.Title.Contains(TextoAPesquisar) && c.CategoriaId == CategoriaId && c.LocadorId == manager.LocadorId
                                        select c;
                        return View(resultado);
                    }
                }
             }

                var aux = from c in _context.Imoveis
                                where c.Title.Contains(TextoAPesquisar) && c.CategoriaId == CategoriaId
                                select c;
                return View(aux);

           
        }

       

        // GET: Imoveis/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null || _context.Imoveis == null)
            {
                return NotFound();
            }

            var imo = await _context.Imoveis.Include("categoria")
                .FirstOrDefaultAsync(m => m.Id == id);
            if (imo == null)
            {
                return NotFound();
            }

            return View(imo);
        }

        // GET: Imoveis/Create
        public async Task<IActionResult> Create()
        {
            var user = await _userManager.GetUserAsync(User);
            var f = await _context.Funcionarios.FindAsync(user.Id);
            var manager = await _context.Managers.FindAsync(user.Id);
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            if(f != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == f.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }
            if (manager != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == manager.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }

            return View();
        }

        // POST: Imoveis/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Title,Descricao,Price,Available,Localizacao,Quartos,DataInit,DataEnd,TempoMin,CategoriaId,LocadorId, ClienteId")] Imovel imovel)
        {
            ModelState.Remove(nameof(imovel.locador));
            ModelState.Remove(nameof(imovel.categoria));
            ModelState.Remove(nameof(imovel.cliente));

            if (ModelState.IsValid)
            {
                _context.Add(imovel);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            var user = await _userManager.GetUserAsync(User);
            var f = await _context.Funcionarios.FindAsync(user.Id);
            var manager = await _context.Managers.FindAsync(user.Id);
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            if (f != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == f.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }
            if (manager != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == manager.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }

            return View(imovel);
        }

        // GET: Imoveis/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {            

            if (id == null || _context.Imoveis == null)
            {
                return NotFound();
            }

            var imo = await _context.Imoveis.FindAsync(id);
            if (imo == null)
            {
                return NotFound();
            }
            var user = await _userManager.GetUserAsync(User);
            var f = await _context.Funcionarios.FindAsync(user.Id);
            var manager = await _context.Managers.FindAsync(user.Id);
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            if (f != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == f.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }
            if (manager != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == manager.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }

            return View(imo);
        }

        // POST: Imoveis/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Title,Descricao,Price,Available,Localizacao,Quartos,DataInit,DataEnd,TempoMin,CategoriaId,LocadorId, ClienteId")] Imovel imovel)
        {
            if (id != imovel.Id)
            {
                return NotFound();
            }

            ModelState.Remove(nameof(imovel.categoria));
            ModelState.Remove(nameof(imovel.locador));
            ModelState.Remove(nameof(imovel.cliente));

            // Verificar se tem cliente associado senao ao editar perde se o cliente associado
            /* var imo = await _context.Imoveis.FindAsync(imovel.Id);
            if(imo.ClienteId != null)
            {
                imovel.ClienteId = imo.ClienteId;
            } */

            if (ModelState.IsValid)
            {
                // imovel.ClienteId = "00bf495c-d1d0-41e1-a3ca-3adb21e220b9";
                try
                {
                    _context.Update(imovel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!ImovelExists(imovel.Id))
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
            var user = await _userManager.GetUserAsync(User);
            var f = await _context.Funcionarios.FindAsync(user.Id);
            var manager = await _context.Managers.FindAsync(user.Id);
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            if (f != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == f.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }
            if (manager != null)
            {
                ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.Where(c => c.Id == manager.LocadorId).OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            }

            return View(imovel);
        }

        // GET: Imoveis/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null || _context.Imoveis == null)
            {
                return NotFound();
            }

            var imo = await _context.Imoveis
                .FirstOrDefaultAsync(m => m.Id == id);
            if (imo == null)
            {
                return NotFound();
            }

            return View(imo);
        }

        // POST: Imoveis/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            if (_context.Imoveis == null)
            {
                return Problem("Entity set 'ApplicationDbContext.Imoveis'  is null.");
            }
            var imo = await _context.Imoveis.FindAsync(id);
            if (imo != null)
            {
                var resultado = from c in _context.Alugados
                                where c.ImovelId == imo.Id && c.State == 1
                                select c;
                int count = resultado.Count();
                if (count == 0)
                {
                    _context.Imoveis.Remove(imo);
                }
            }
            
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool ImovelExists(int id)
        {
          return (_context.Imoveis?.Any(e => e.Id == id)).GetValueOrDefault();
        }

    }
}
